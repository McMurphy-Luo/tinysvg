#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>
#include <vector>
#include <cassert>
#include <memory>

#ifdef __cpp_lib_optional
#include <optional>
#else
#include <type_traits>
#endif// __cpp_lib_optional

NAMESPACE_BEGIN

#ifdef __cpp_lib_optional

using std::optional;
using std::make_optional;
using std::nullopt;
using std::nullopt_t;

#else // __cpp_lib_optional

struct in_place_t {
  explicit in_place_t() = default;
};
constexpr in_place_t in_place{};

struct nullopt_t {
  explicit constexpr nullopt_t(int) {}
};
constexpr nullopt_t nullopt{0};

template<typename T>
class optional_base
{
public:
  optional_base()
    : value_(nullptr)
  {

  }

  template<typename... Args>
  optional_base(in_place_t, Args&&... args)
    : value_(std::make_unique<T>(std::forward<Args>(args)...))
  {

  }

  optional_base(nullopt_t)
    : value_(nullptr)
  {

  }

  optional_base(optional_base&& another)
    : value_(std::move(another.value_))
  {

  }

  optional_base& operator=(optional_base<T>&& another)
  {
    value_ = std::move(another.value_);
    return *this;
  }

  optional_base(T&& another) noexcept
    : value_(std::make_unique<T>(std::move(another)))
  {

  }

  optional_base& operator=(T&& another) noexcept
  {
    *value_ = another;
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

  const T& value() const {
    assert(value_);
    return *value_;
  }

protected:
  std::unique_ptr<T> value_;
};

template<typename T>
class optional_copyable : public optional_base<T>
{
public:
  optional_copyable()
    : optional_base<T>()
  {

  }

  optional_copyable(nullopt_t)
    : optional_base<T>(nullopt)
  {

  }

  optional_copyable(const optional_copyable& another)
    : optional_base<T>(nullopt)
  {
    if (another.has_value()) {
      this->value_ = std::make_unique<T>(another.value());
    }
  }
  
  optional_copyable& operator=(const optional_copyable& another)
  {
    if (this == &another) {
      return *this;
    }
    if (!another.has_value()) {
      this->value_.reset();
    }
    else if (another.has_value() && this->has_value()) {
      *(this->value_) = *(another.value_);
    }
    else {
      this->value_ = std::make_unique<T>(*(another.value_));
    }
    return *this;
  }
  
  optional_copyable(const T& value)
    : optional_base<T>(nullopt)
  {
    if (this->has_value()) {
      *(this->value_) = value;
    }
    else {
      this->value_ = std::make_unique<T>(value);
    }
  }

  optional_copyable& operator=(const T& another)
  {
    if (this->has_value()) {
      *(this->value_) = another;
    }
    else {
      this->value_ = std::make_unique<T>(another);
    }
    return *this;
  }
};

template<typename T>
using optional =
typename std::conditional<
  std::is_copy_assignable<T>::value && std::is_copy_constructible<T>::value,
  optional_copyable<T>,
  optional_base<T>
>::type;

template<typename T, typename... Args>
constexpr optional<T> make_optional(Args&&... args)
{
  return optional<T>(in_place, std::forward<Args>(args)...);
}

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

struct SvgNone
{
  static constexpr SvgType Type = SvgType::None;
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

  NodeDelegateBase(NodeDelegateBase&& another) noexcept
  : the_node_(std::move(another.the_node_))
  {

  }

  NodeDelegateBase& operator=(NodeDelegateBase&& another) noexcept {
    the_node_ = std::move(another.the_node_);
    return *this;
  }

  SvgType const Type() { return the_node_->Type(); }

  template<typename T>
  optional<NodeDelegate<T>> To() {
    if (std::dynamic_pointer_cast<Node<T>>(the_node_)) {
      return make_optional<NodeDelegate<T>>(std::dynamic_pointer_cast<Node<T>>(the_node_));
    }
    return optional<NodeDelegate<T>>();
  }

protected:
  std::shared_ptr<NodeBase> the_node_;
};

template<typename T>
class NodeDelegate: public NodeDelegateBase {
protected:
  NodeDelegate(std::shared_ptr<Node<T>> node)
    :NodeDelegateBase(node)
  {
    // do nothing
  }

  NodeDelegate(const NodeDelegate<T>& another) = delete;

  NodeDelegate& operator=(const NodeDelegate<T>& another) = delete;

public:
  NodeDelegate(NodeDelegate<T>&& another)
    : NodeDelegateBase(another.the_node_)
  {

  }

  NodeDelegate& operator=(NodeDelegate<T>&& another)
  {
    return *this;
  }

  NodeDelegateBase FirstChild() const;

  NodeDelegateBase NextSibling() const;

  template<typename T>
  NodeDelegate<T> AddChild(const T& target) {
    std::shared_ptr<Node<T>> child_new_created = std::make_shared<Node<T>>(target);
    the_node_->children.push_back(child_new_created);
    return NodeDelegate<T>(child_new_created);
  }

  void Detach();

  T& Value() {
    assert(Type() == T::Type);
    return std::dynamic_pointer_cast<Node<T>>(the_node_)->Value();
  }

  const T& Value() const {
    assert(Type() == T::Type);
    return std::dynamic_pointer_cast<Node<T>>(the_node_)->Value();
  }
};

NAMESPACE_END

#endif // TINYSVG_SVGBASE_H_