#ifndef TINYSVG_SVG_SVGPOINT_H_
#define TINYSVG_SVG_SVGPOINT_H_

#include "../Config.h"
#include "./SVGLength.h"
#include <cmath>

NAMESPACE_BEGIN

class SVGPoint {
public:
    SVGPoint(SVGLength x, SVGLength y) :
        x_(x),
        y_(y) {
        // do nothing
    }

    SVGPoint(): SVGPoint(SVGLength()) {

    }

    SVGLength X() const { return x_; }

    SVGLength Y() const { return y_; }

    void SetX(SVGLength value) { x_ = value; }

    void SetY(SVGLength value) { y_ = value; }
       
private:
    SVGLength x_;
    SVGLength y_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGPOINT_H_