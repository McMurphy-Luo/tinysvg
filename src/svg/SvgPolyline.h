#ifndef TINYSVG_SVGPOLYLINE_H_
#define TINYSVG_SVGPOLYLINE_H_

#include "../Config.h"
#include <vector>
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgPolyline
  : public SvgBase
{
public:
  SvgPolyline(const std::vector<SvgPoint>& points)
    : SvgBase(SvgType::SvgPolyline)
    , points_(points)
  {

  }

  SvgPolyline()
  : SvgPolyline(std::vector<SvgPoint>())
  {

  }

  std::vector<SvgPoint> Points() { return points_; }

private:
  std::vector<SvgPoint> points_;
};

NAMESPACE_END

#endif // TINYSVG_SVGPOLYLINE_H_