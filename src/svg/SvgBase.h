#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>
#include <vector>

#ifdef __cpp_lib_optional
#include <optional>
#else
#include <cassert>
#include <memory>
#endif// __cpp_lib_optional

NAMESPACE_BEGIN

typedef double_t SvgLength;

#ifdef __cpp_lib_optional

using std::optional;

#else // __cpp_lib_optional

template<typename T>
class optional
{
public:
  optional()
  : value_(nullptr)
  {

  }

  optional(const optional<T>& another)
  : value_(nullptr)
  {
    if (another.has_value()) {
      value_ = std::make_unique<T>(*(another.value_));
    }
  }

  optional(const T& value)
  {
    value_ = std::make_unique<T>(value);
  }

  optional& operator=(const optional<T>& another)
  {
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

  optional& operator=(const T& another)
  {
    if (has_value()) {
      *value_ = another;
    }
    else {
      value_ = std::make_unique<T>(another);
    }
    return *this;
  }

  operator bool() const
  {
    return has_value();
  }

  bool has_value() const
  {
    if (value_) {
      return true;
    }
    else {
      return false;
    }
  }

  T& value()
  {
    assert(value_);
    return *value_;
  }

private:
  std::unique_ptr<T> value_;
};

#endif

enum class SvgType
{
  SvgSvg,
  SvgRectangle,
  SvgLine,
  SvgEllipse,
  SvgPolygon,
  SvgPath,
  SvgCircle,
  SvgPolyline
};

struct SvgPoint
{
  SvgLength x;
  SvgLength y;
};

class SvgBase
{
public:
  SvgBase(SvgType type)
  : type_(type)
  , children_()
  , parent_()
  {

  }

  virtual ~SvgBase()
  {

  }

  void AddChild(std::shared_ptr<SvgBase>& target);

  void RemoveChild(std::shared_ptr<SvgBase>& child);

  SvgType Type() const { return type_; }

private:
  SvgType type_;
  std::vector<std::shared_ptr<SvgBase>> children_;
  std::weak_ptr<SvgBase> parent_;
};

NAMESPACE_END

#endif // TINYSVG_SVGBASE_H_