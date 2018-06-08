#ifndef TINYSVG_SVG_SVGLENGTH_H_
#define TINYSVG_SVG_SVGLENGTH_H_

#include "../Config.h"
#include <cmath>
#include <better-enums/enum.h>

NAMESPACE_BEGIN

enum class SVGUnit {
    Px,
    Percent
};

struct SVGLength {
    SVGLength(double_t value, SVGUnit) {

    }
    double_t value;
    SVGUnit unit;
};

NAMESPACE_END


#endif // TINYSVG_SVG_SVGLENGTH_H_