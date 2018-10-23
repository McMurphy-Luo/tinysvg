#include "./SvgDocumentParser.h"
#include <cassert>
#include <tinyxml2/tinyxml2.h>
#include "../common/DomString.h"
#include "../svg/SvgRect.h"
#include "../svg/SvgLine.h"

using std::size_t;
using std::pair;
using std::make_pair;
using std::shared_ptr;
using tinyxml2::XMLDocument;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

namespace { // unamed namespace for this file static staff
  shared_ptr<SvgSvg> ParseSvgElement(XMLElement* element)
  {
    return nullptr;
  }

  shared_ptr<SvgRect> ParseSvgRect(XMLElement* element)
  {
    return nullptr;
  }

  shared_ptr<SvgLine> ParseSVGLine(XMLElement* element)
  {
    DomString element_name(element->Name());
    assert(element_name == "line");
    return nullptr;
  }

  shared_ptr<SvgBase> ParseElement(XMLElement* element)
  {
    DomString element_name(element->Name());
    DomString element_name_lowered = element_name.ToLower();
    if (element_name_lowered == "SVG") {
      return ParseSvgElement(element);
    }
    else if (element_name_lowered == "rect") {
      return ParseSvgRect(element);
    }
    else if (element_name_lowered == "line") {
      return ParseSVGLine(element);
    }
    else {
      assert(false);
      return nullptr;
    }
  }
} // end unamed namespace

pair<bool, SvgSvg> SVGDocumentParser::Parse(const char* buffer, size_t buffer_size)
{
  tinyxml2::XMLDocument document;
  tinyxml2::XMLError error = document.Parse(buffer, buffer_size);
  if (error != XML_SUCCESS) {
    return make_pair(false, SvgSvg());
  }
  XMLElement* root = document.RootElement();
  DomString nodeName(root->Name());
  if (nodeName.ToLower() != "svg") {
    return make_pair(false, SvgSvg());
  }
  const char* viewBox = root->Attribute("viewBox");
  if (root->NoChildren()) {
    return make_pair(true, SvgSvg());
  }
  SvgSvg theSVGObject;
  for (XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement()) {

  }

  return { false, SvgSvg() };
}

NAMESPACE_END
