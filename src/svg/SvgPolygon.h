#ifndef TINYSVG_SVGPOLYGON_H_
#define TINYSVG_SVGPOLYGON_H_

#include "../Config.h"
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgPolygon
{
public:
  static constexpr SvgType Type = SvgType::Polygon;

public:
  SvgPolygon()
  {

  }
};

NAMESPACE_END

#endif // TINYSVG_SVGPOLYGON_H_