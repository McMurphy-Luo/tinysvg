#ifndef TINYSVG_CONVERT_H_
#define TINYSVG_CONVERT_H_

#include "../Config.h"
#include <utility>
#include "./DomString.h"

NAMESPACE_BEGIN

std::pair<bool, int> ToInt(const DomString& value);

std::pair<bool, double> ToDouble(const DomString& value);

NAMESPACE_END

#endif // TINYSVG_CONVERT_H_