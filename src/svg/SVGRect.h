#ifndef EASY_SVG_SVG_RECT_H_
#define EASY_SVG_SVG_RECT_H_

#include "../Config.h"
#include "./SVGLength.h"

NAMESPACE_BEGIN

class SVGRect {
public:
    SVGRect(SVGLength left, SVGLength top, SVGLength right, SVGLength bottom)
        :left_(left),
        top_(top),
        right_(right),
        bottom_(bottom)
    {

    }

    Left() { return left_; }

    void SetLeft(SVGLength value) { left_ = value; }

    Top() { return top_; }

    void SetTop(SVGLength value) { top_ = value; }

    Right() { return right_; }

    void SetRight(SVGLength value) { right_ = value; }

    Bottom() { return bottom_; }

    void SetBottom(SVGLength value) { bottom_ = value; }

private:
    SVGLength left_;
    SVGLength top_;
    SVGLength right_;
    SVGLength bottom_;
};

NAMESPACE_END


#endif // EASY_SVG_SVG_RECT_H_