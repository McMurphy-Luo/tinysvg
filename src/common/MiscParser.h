#ifndef TINYSVG_MISC_PARSER_H_
#define TINYSVG_MISC_PARSER_H_

#include "../Config.h"
#include <vector>
#include <utility>
#include "../common/DomString.h"
#include "../svg/SvgBase.h"

NAMESPACE_BEGIN

std::pair<bool, std::vector<SvgLength>> ParseNumericList(const DomString& source);

std::pair<bool, SvgLength> ParseNumeric(const DomString& source);

NAMESPACE_END

#endif // TINYSVG_MISC_PARSER_H_