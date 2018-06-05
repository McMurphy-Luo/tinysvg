#ifndef TINYSVG_SVG_SVGLENGTH_H_
#define TINYSVG_SVG_SVGLENGTH_H_

#include "../Config.h"
#include <cmath>

NAMESPACE_BEGIN

enum class SVGUnit {
    Px,
    Percent
};

struct SVGLength {
    double_t value;
    SVGUnit unit;
};

NAMESPACE_END


#endif // TINYSVG_SVG_SVGLENGTH_H_