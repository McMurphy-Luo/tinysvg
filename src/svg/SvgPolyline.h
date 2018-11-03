#ifndef TINYSVG_SVGPOLYLINE_H_
#define TINYSVG_SVGPOLYLINE_H_

#include "../Config.h"
#include <vector>
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgPolyline
{
public:
  SvgPolyline(const std::vector<SvgPoint>& points)
    : points_(points)
  {
    // do nothing
  }

  SvgPolyline()
    : SvgPolyline(std::vector<SvgPoint>())
  {
    // do nothing
  }

  std::vector<SvgPoint> Points() { return points_; }

private:
  std::vector<SvgPoint> points_;
};

NAMESPACE_END

#endif // TINYSVG_SVGPOLYLINE_H_