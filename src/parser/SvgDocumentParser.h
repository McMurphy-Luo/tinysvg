#ifndef TINYSVG_PARSER_SVGDOCUMENTPARSER_H_
#define TINYSVG_PARSER_SVGDOCUMENTPARSER_H_

#include "../Config.h"
#include <cstddef>
#include <utility>
#include "../svg/SvgSvg.h"
#include "../svg/SvgBase.h"
#include "../svg/SvgDocument.h"

NAMESPACE_BEGIN

optional<SvgDocument<SvgSvg>> Parse(const char* buffer, std::size_t buffer_size);

NAMESPACE_END

#endif // TINYSVG_PARSER_SVGDOCUMENTPARSER_H_