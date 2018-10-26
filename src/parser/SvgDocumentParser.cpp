#include "./SvgDocumentParser.h"

#include <cassert>
#include <tinyxml2/tinyxml2.h>

#include "../common/DomString.h"
#include "../svg/SvgRect.h"
#include "../svg/SvgLine.h"
#include "../common/Convert.h"

using std::size_t;
using std::pair;
using std::make_pair;
using std::shared_ptr;
using std::vector;
using tinyxml2::XMLDocument;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

namespace { // unamed namespace for this file static staff
  shared_ptr<SvgRect> ParseSvgRectElement(XMLElement* element)
  {
    return nullptr;
  }

  shared_ptr<SvgLine> ParseSVGLineElement(XMLElement* element)
  {
    DomString element_name(element->Name());
    assert(element_name == u8"line");
    return nullptr;
  }

  pair<bool, SvgSvg> ParseSvgElement(XMLElement* target)
  {
    DomString nodeName(target->Name());
    assert(nodeName == DomString(u8"svg"));
    if (nodeName != DomString(u8"svg")) {
      return make_pair(false, SvgSvg());
    }
    
    DomString viewBox = DomString(target->Attribute(u8"viewBox"));
    vector<DomString> viewBox_number_separated = viewBox.Split(",");

    

    for (const DomString& item : viewBox_number_separated) {
      StringToDouble(item);
    }

    if (target->NoChildren()) {
      return make_pair(true, SvgSvg());
    }

    return { false, SvgSvg() };
  }
} // end unamed namespace

pair<bool, SvgSvg> SVGDocumentParser::Parse(const char* buffer, size_t buffer_size)
{
  tinyxml2::XMLDocument document;
  tinyxml2::XMLError error = document.Parse(buffer, buffer_size);
  if (error != XML_SUCCESS) {
    return make_pair(false, SvgSvg());
  }
  return ParseSvgElement(document.RootElement());
}

NAMESPACE_END
