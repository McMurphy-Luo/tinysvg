#include "./SvgColor.h"

NAMESPACE_BEGIN

bool ParseColorFromString(const DomString& target, SVGColor& output)
{
    if (target.ChararcterCount() != 4 && target.ChararcterCount() != 5 && target.ChararcterCount() != 7 && target.ChararcterCount() != 9) {
        return false;
    }
    if (target.CharAt(0) != u8'#') {
        return false;
    }
    double red = 0;
    double green = 0;
    double blue = 0;
    double alpha = 0;
    return true;
}

NAMESPACE_END