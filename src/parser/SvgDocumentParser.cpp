#include "./SVGDocumentParser.h"
#include <cassert>
#include <tinyxml2/tinyxml2.h>
#include "../common/DOMString.h"
#include "../svg/SVGRect.h"
#include "../svg/SVGLine.h"

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
  shared_ptr<SVGSVG> ParseSVGElement(XMLElement* element) {

  }

  shared_ptr<SVGRect> ParseSVGRect(XMLElement* element) {

  }

  shared_ptr<SVGLine> ParseSVGLine(XMLElement* element) {
    DOMString element_name(element->Name());
    assert(element_name == "line");
  }

  shared_ptr<SVGBase> ParseElement(XMLElement* element) {
    DOMString element_name(element->Name());
    DOMString element_name_lowered = element_name.ToLower();
    if (element_name_lowered == "SVG") {
      return ParseSVGElement(element);
    }
    else if (element_name_lowered == "rect") {
      return ParseSVGRect(element);
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

SVGDocumentParser::SVGDocumentParser() {
  // do nothing for now
}

pair<bool, SVGSVG> SVGDocumentParser::Parse(const char* buffer, size_t buffer_size) {
  tinyxml2::XMLDocument document;
  tinyxml2::XMLError error = document.Parse(buffer, buffer_size);
  if (error != XML_SUCCESS) {
    return make_pair(false, SVGSVG());
  }
  XMLElement* root = document.RootElement();
  DOMString nodeName(root->Name());
  if (nodeName.ToLower != "svg") {
    return make_pair(false, SVGSVG());
  }
  const char* viewBox = root->Attribute("viewBox");
  if (root->NoChildren()) {
    return make_pair(true, SVGSVG());
  }
  SVGSVG theSVGObject;

  for (XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement()) {

  }


}

NAMESPACE_END
