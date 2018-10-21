#ifndef TINYSVG_SVG_SVGPOLYLINE_H_
#define TINYSVG_SVG_SVGPOLYLINE_H_

#include "../Config.h"
#include <vector>
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SVGPolyline {
public:
    SVGPolyline(const std::vector<SvgPoint>& points)
    : points_(points) {

    }

    std::vector<SvgPoint> Points() { return points_; }

private:
    std::vector<SvgPoint> points_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGPOLYLINE_H_