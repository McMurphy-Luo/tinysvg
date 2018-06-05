#ifndef TINYSVG_SVG_SVGPOINT_H_
#define TINYSVG_SVG_SVGPOINT_H_

#include "../Config.h"
#include <cmath>

NAMESPACE_BEGIN

class SVGPoint {
public:
    SVGPoint(double_t x, double_t y) :
        x_(x),
        y_(y) {
        // do nothing
    }

    double_t X() const { return x_; }

    double_t Y() const { return y_; }

    void SetX(double_t value) { x_ = value; }

    void SetY(double_t value) { y_ = value; }
       
private:
    double_t x_;
    double_t y_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGPOINT_H_