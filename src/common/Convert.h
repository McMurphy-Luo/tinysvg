#ifndef TINYSVG_CONVERT_H_
#define TINYSVG_CONVERT_H_

#include "../Config.h"
#include <utility>
#include "./DomString.h"

NAMESPACE_BEGIN

std::pair<bool, int> StringToInt(const DomString& value);

std::pair<bool, double> StringToDouble(const DomString& value);

DomString IntToString(int value);

DomString DoubleToString(double value);

NAMESPACE_END

#endif // TINYSVG_CONVERT_H_