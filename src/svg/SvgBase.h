#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <type_traits>

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

  optional(nullptr_t)
    : value_(nullptr) {

  }

  template<typename T, typename std::enable_if<std::is_copy_constructible<T>::value || std::is_trivial<T>::value, int>::type = 0>
  optional(const optional<T>& another)
  : value_(nullptr) {
    if (another.has_value()) {
      value_ = std::make_unique<T>(*(another.value_));
    }
  }

  template<typename T, typename std::enable_if<(std::is_copy_constructible<T>::value && std::is_copy_assignable<T>::value) || std::is_trivial<T>::value, int>::type = 0>
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

  template<typename std::enable_if<std::is_copy_constructible<T>::value, int>::type = 0>
  optional(const T& value) {
    value_ = std::make_unique<T>(value);
  }

  template<typename std::enable_if<std::is_copy_assignable<T>::value && std::is_copy_assignable<T>::value || std::is_trivial<T>::value, int>::type = 0>
  optional<T>& operator=(const T& another) {
    if (has_value()) {
      *value_ = another;
    }
    else {
      value_ = std::make_unique<T>(another);
    }
    return *this;
  }

  optional(optional<T>&& another)
  : value_(std::move(another.value_)) {

  }

  template<typename = std::enable_if<std::is_move_constructible<T>::value>>
  optional<T>& operator=(optional<T>&& another) {
    value_ = std::move(another.value_);
    return *this;
  }

  template<typename = std::enable_if<std::is_move_constructible<T>::value>>
  optional<T>& operator=(T&& another) {
    if (has_value()) {
      value_.reset();
    }
    value_ = std::make_unique<T>(another);
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

enum class SvgType
{
  None,
  Line,
  Circle,
  Rectangle,
  Ellipse,
  Polygon,
  Polyline,
  Rect,
  Svg
};

struct NodeBase
{
  virtual ~NodeBase() {}
  virtual SvgType Type() const = 0;
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

  virtual SvgType Type() const { return T::Type; }

  T& Value() { return data_; }

  const T& Value() const { return data_; }

private:
  T data_;
};

template<>
class Node<nullptr_t>
  : public NodeBase
{
public:
  explicit Node() {

  }

public:
  virtual SvgType Type() const { return SvgType::Circle; }
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
  NodeDelegateBase(const NodeDelegateBase& another) = delete;

  NodeDelegateBase& operator=(const NodeDelegateBase& another) = delete;

  NodeDelegateBase(NodeDelegateBase&& another)
  : the_node_(another.the_node_) {
    another.the_node_.reset();
  }

  NodeDelegateBase& operator=(NodeDelegateBase&& another) {
    the_node_.reset();
    the_node_.swap(another.the_node_);
    return *this;
  }

public:
  SvgType const Type() { return the_node_->Type(); }

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

  void Detach();

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

  NodeDelegate(const NodeDelegate<T>& another) = delete;

  NodeDelegate& operator=(const NodeDelegate<T>& another) = delete;

  NodeDelegate(NodeDelegate<T>&& another)
    :NodeDelegateBase(another.the_node_) {

  }

  NodeDelegate& operator=(NodeDelegate<T>&& another) {
    return *this;
  }

  T& Value() {
    assert(Type() == T::Type);
    return std::dynamic_pointer_cast<Node<T>>(the_node_)->Value();
  }

  const T& Value() const {
    assert(Type() == T::Type);
    return std::dynamic_pointer_cast<Node<T>>(the_node_)->Value();
  }
};

template<>
class NodeDelegate<nullptr_t> : public NodeDelegateBase {
public:
  NodeDelegate()
    : NodeDelegateBase(std::make_shared<Node<nullptr_t>>()) {

  }
};

NAMESPACE_END

#endif // TINYSVG_SVGBASE_H_