#include "./Color.h"

NAMESPACE_BEGIN

bool ParseColorFromString(const Utf8String& target, Color& output) {
    if (target.CharacterCount() != 4 && target.CharacterCount() != 5 && target.CharacterCount() != 7 && target.CharacterCount() != 9) {
        return false;
    }
    if (target.CharAt(0) != '#') {
        return false;
    }
    double red = 0;
    double green = 0;
    double blue = 0;
    double alpha = 0;
    return true;
}

bool ParseColorFromString(const Utf8String& target, ColorF& output) {
    return true;
}

NAMESPACE_END