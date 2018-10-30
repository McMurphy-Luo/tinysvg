#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>

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
class optional {
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

  optional& operator=(const optional<T>& another)
  {
    if (this == &another) {
      return *this;
    }
    if (another.has_value()) {
      value_ = std::make_unique<T>(*(another.value_));
    }
  }

  optional(const T& value)
  {
    value_ = std::make_unique<T>(value);
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

enum class SvgType {
  SvgSvg,
  SvgRectangle,
  SvgLine,
  SvgEllipse,
  SvgPolygon,
  SvgPath,
  SvgCircle,
  SvgPolyline
};

struct SvgPoint {
  SvgLength x;
  SvgLength y;
};

class SvgBase {
public:
  SvgBase(SvgType type) {

  }

  SvgType Type() const { return type_; }

private:
  SvgType type_;
};

NAMESPACE_END

#endif // TINYSVG_SVGBASE_H_