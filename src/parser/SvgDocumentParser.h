#ifndef TINYSVG_PARSER_SVGDOCUMENTPARSER_H_
#define TINYSVG_PARSER_SVGDOCUMENTPARSER_H_

#include "../Config.h"
#include <cstddef>
#include <utility>
#include "../svg/SvgSvg.h"

NAMESPACE_BEGIN

std::pair<bool, SvgSvg> Parse(const char* buffer, std::size_t buffer_size);

NAMESPACE_END

#endif // TINYSVG_PARSER_SVGDOCUMENTPARSER_H_