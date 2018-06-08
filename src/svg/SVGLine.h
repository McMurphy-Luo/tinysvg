#ifndef TINYSVG_SVG_SVGLINE_H_
#define TINYSVG_SVG_SVGLINE_H_

#include "../Config.h"
#include "./SVGBase.h"
#include "./SVGPoint.h"

NAMESPACE_BEGIN

class SVGLine : public SVGBase {
public:
    SVGLine() : SVGBase(SVGType::SVGLine): p1() {

    }

    

private:
    SVGPoint p1_;
    SVGPoint p2_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGLINE_H_