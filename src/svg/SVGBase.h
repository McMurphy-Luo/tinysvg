#ifndef TINYSVG_SVG_SVGBASE_H_
#define TINYSVG_SVG_SVGBASE_H_

#include "../Config.h"

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

class SvgBase {
public:
  SvgBase(SvgType type) {

  }


private:
  SvgType type_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGBASE_H_