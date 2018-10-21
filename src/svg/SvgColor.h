#ifndef TINYSVG_SVG_SVGCOLOR_H_
#define TINYSVG_SVG_SVGCOLOR_H_

#include "../Config.h"
#include <cstdint>
#include <cmath>
#include "../common/DomString.h"

NAMESPACE_BEGIN

class SVGColor;

bool ParseColorFromString(const DomString& target, SVGColor& output);

class SVGColor {
public:
    static SVGColor Transparent() { return SVGColor(0, 0, 0, 100); }

public:
    SVGColor(std::uint_fast8_t red, std::uint_fast8_t green, std::uint_fast8_t blue, std::uint_fast8_t alpha) :
        red_(red),
        green_(green),
        blue_(blue),
        alpha_(alpha) {
        // do nothing
    }

    SVGColor(std::uint_fast8_t red, std::uint_fast8_t green, std::uint_fast8_t blue) :
        SVGColor(red, green, blue, 100) {
        // do nothing
    }

    SVGColor() : SVGColor(Transparent()) {
        // do nothing
    }

    std::uint_fast8_t Red() { return red_; }

    void SetRed(std::uint_fast8_t value) { red_ = value; }

    std::uint_fast8_t Green() { return green_; }

    void SetGreen(std::int_fast8_t value) { green_ = value; }

    std::uint_fast8_t Blue() { return blue_; }

    void SetBlue(std::int_fast8_t value) { blue_ = value; }

    std::int_fast8_t Alpha() { return alpha_; }

    void SetAlpha(std::int_fast8_t value) { alpha_ = value; }

private:
    std::uint_fast8_t red_;
    std::uint_fast8_t green_;
    std::uint_fast8_t blue_;
    std::uint_fast8_t alpha_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGCOLOR_H_