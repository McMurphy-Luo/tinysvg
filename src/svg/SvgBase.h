#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>

#ifdef __cpp_lib_optional
#include <optional>
#endif // __cpp_lib_optional

NAMESPACE_BEGIN

typedef double_t SvgLength;

#ifdef __cpp_lib_optional

using std::optional;

#else // __cpp_lib_optional

template<typename T>
class optional {

  bool operator bool() const noexcept
  {

  }

  bool has_value() const noexcept {

  }
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