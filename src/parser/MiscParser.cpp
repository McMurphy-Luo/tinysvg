#include "./MiscParser.h"

#include <cctype>
#include <cassert>

using std::vector;
using std::pair;
using std::size_t;
using std::isspace;

NAMESPACE_BEGIN

pair<bool, SvgLength> ParseNumeric(const DomString& source)
{
  const char* pointer_begin = source.Data();
  char* pointer_end = const_cast<char*>(pointer_begin) + source.ByteCount();

  double value = strtod(pointer_begin, &pointer_end);
}

NAMESPACE_END