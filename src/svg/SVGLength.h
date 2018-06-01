#ifndef EASY_SVG_COMMON_LENGTH_H_
#define EASY_SVG_COMMON_LENGTH_H_


#include "../Config.h"
#include <cmath>

NAMESPACE_BEGIN

enum class SVGUnit {
    Px,
    Percent
};

struct SVGLength {
    double_t value;
    SVGUnit unit
};

NAMESPACE_END


#endif //