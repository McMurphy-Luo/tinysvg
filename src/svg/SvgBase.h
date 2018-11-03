#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>
#include <vector>
#include <algorithm>

#ifdef __cpp_lib_optional
#include <optional>
#else
#include <cassert>
#include <memory>
#endif// __cpp_lib_optional

NAMESPACE_BEGIN

#ifdef __cpp_lib_optional

using std::optional;

#else // __cpp_lib_optional

template<typename T>
class optional
{
public:
  optional()
  : value_(nullptr) {

  }

  optional(const optional<T>& another)
  : value_(nullptr) {
    if (another.has_value()) {
      value_ = std::make_unique<T>(*(another.value_));
    }
  }

  optional(nullptr_t)
  : value_(nullptr) {

  }

  optional(const T& value) {
    value_ = std::make_unique<T>(value);
  }

  optional& operator=(const optional<T>& another) {
    if (this == &another) {
      return *this;
    }
    if (!another.has_value()) {
      value_.reset();
    }
    else if (another.has_value() && has_value()) {
      *value_ = *(another.value_);
    }
    else {
      value_ = std::make_unique<T>(*(another.value_));
    }
    return *this;
  }

  optional& operator=(const T& another) {
    if (has_value()) {
      *value_ = another;
    }
    else {
      value_ = std::make_unique<T>(another);
    }
    return *this;
  }

  operator bool() const {
    return has_value();
  }

  bool has_value() const {
    if (value_) {
      return true;
    }
    else {
      return false;
    }
  }

  T& value() {
    assert(value_);
    return *value_;
  }

private:
  std::unique_ptr<T> value_;
};

#endif

typedef double_t SvgLength;

struct SvgPoint
{
  SvgLength x;
  SvgLength y;
};

struct NodeBase
{
  std::vector<std::shared_ptr<NodeBase>> children;
  std::weak_ptr<NodeBase> parent;
};

template<typename T>
class Node
  : public NodeBase
{
public:
  explicit Node(const T& svg)
    : data_(svg) {
    // do nothing
  }

  T& Value() { return data_; }

  const T& Value() const { return data_; }

private:
  T data_;
};

template<typename T>
class NodeDelegate;

class NodeDelegateBase
{
protected:
  explicit NodeDelegateBase(std::shared_ptr<NodeBase> the_node)
    : the_node_(the_node)
  {
    assert(the_node);
  }

public:
  template<typename T>
  NodeDelegate<T> AddChild(const T& target) {
    std::shared_ptr<Node<T>> child_new_created = std::make_shared<Node<T>>(target);
    the_node_->children.push_back(child_new_created);
    return NodeDelegate<T>(child_new_created);
  }

  template<typename T>
  optional<NodeDelegate<T>> To() {
    optional<NodeDelegate<T>> result;
    if (std::dynamic_pointer_cast<Node<T>>(the_node_)) {
      result = NodeDelegate<T>(std::dynamic_pointer_cast<Node<T>>(the_node_));
    }
    return result;
  }

  void Detach() {
    if (!the_node_->parent.expired()) {
      std::shared_ptr<NodeBase> parent = the_node_->parent.lock();
      parent->children.erase(
        std::remove(
          parent->children.begin(),
          parent->children.end(),
          the_node_
        ),
        parent->children.end()
      );
    }
  }

protected:
  std::shared_ptr<NodeBase> the_node_;
};

template<typename T>
class NodeDelegate: public NodeDelegateBase {
public:
  NodeDelegate(std::shared_ptr<Node<T>> node)
    :NodeDelegateBase(node)
  {
    // do nothing
  }

public:
  T& Value() { return the_node_->Value(); }

  const T& Value() const { return the_node_->Value(); }
};

NodeDelegate<nullptr_t> EmptyNode() {
  return NodeDelegate<nullptr_t>(
    std::make_shared<Node<nullptr_t>>(nullptr)
    );
}

NAMESPACE_END

#endif // TINYSVG_SVGBASE_H_