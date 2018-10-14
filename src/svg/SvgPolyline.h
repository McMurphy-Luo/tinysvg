#ifndef TINYSVG_SVG_SVGPOLYLINE_H_
#define TINYSVG_SVG_SVGPOLYLINE_H_

#include "../Config.h"
#include <vector>
#include "./SVGPoint.h"

NAMESPACE_BEGIN

class SVGPolyline {
public:
    SVGPolyline(const std::vector<SVGPoint>& points):points_(points) {

    }

    std::vector<SVGPoint> Points() { return points_; }

private:
    std::vector<SVGPoint> points_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGPOLYLINE_H_