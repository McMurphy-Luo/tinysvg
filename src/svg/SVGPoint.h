#ifndef EASY_SVG_COMMON_POINT_H_
#define EASY_SVG_COMMON_POINT_H_

#include "../Config.h"
#include "./SVGLength.h"

NAMESPACE_BEGIN

class SVGPoint {
public:
    SVGPoint(int x, int y) :
        x_(x),
        y_(y) {
        // do nothing
    }

    int X() const { return x_; }

    int Y() const { return y_; }

    void SetX(int value) { x_ = value; }

    void SetY(int value) { y_ = value; }

    void Offset(int x, int y) { x_ += x; y_ += y; }

    int Distance(const Point& another) {
        return static_cast<int>(std::round(
            std::sqrt(
                std::pow(another.X() - X(), 2) + std::pow(another.Y() - Y(), 2)
            )
        ));
    }

    Point Middle(const Point& another) {
        return Point((X() + another.X()) / 2, (Y() + another.Y()) / 2);
    }
       
private:
    int x_;
    int y_;
};


NAMESPACE_END

#endif // EASY_SVG_COMMON_POINT_H_