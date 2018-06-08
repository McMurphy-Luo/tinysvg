#ifndef TINYSVG_SVG_SVGBASE_H_
#define TINYSVG_SVG_SVGBASE_H_

#include "../Config.h"

NAMESPACE_BEGIN

enum class SVGType {
    SVGSVG,
    SVGRectangle,
    SVGLine,
    SVGEllipse,
    SVGPolygon,
    SVGPath,
    SVGCircle,
    SVGPolyline
};

class SVGBase {
public:
    SVGBase(SVGType type) {

    }


private:
    SVGType type_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGBASE_H_