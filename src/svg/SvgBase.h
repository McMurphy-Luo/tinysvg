#ifndef TINYSVG_SVGBASE_H_
#define TINYSVG_SVGBASE_H_

#include "../Config.h"
#include <cmath>

NAMESPACE_BEGIN

typedef double_t SvgLength;

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