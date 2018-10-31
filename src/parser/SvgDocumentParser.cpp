#include "./SvgDocumentParser.h"

#include <cassert>
#include "tinyxml2/tinyxml2.h"

#include "../common/DomString.h"
#include "../svg/SvgRect.h"
#include "../svg/SvgLine.h"
#include "../svg/SvgEllipse.h"
#include "../svg/SvgPolygon.h"
#include "../svg/SvgPolyline.h"
#include "../svg/SvgCircle.h"
#include "./MiscParser.h"

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
    SvgSvg result;
    DomString viewBox = DomString(target->Attribute(u8"viewBox"));
    pair<bool, vector<SvgLength>> viewBox_parsed = ParseNumericList(viewBox);
    if (viewBox_parsed.first) {
      SvgSvg::SvgViewBox viewbox;
      if (viewBox_parsed.second.size() > 0) {
        viewbox.x = viewBox_parsed.second[0];
      }
      if (viewBox_parsed.second.size() > 1) {
        viewbox.y = viewBox_parsed.second[1];
      }
      if (viewBox_parsed.second.size() > 2) {
        viewbox.width = viewBox_parsed.second[2];
      }
      if (viewBox_parsed.second.size() > 3) {
        viewbox.height = viewBox_parsed.second[3];
      }
      result.SetViewBox(viewbox);
    }

    XMLElement* child = target->FirstChildElement();
    while (child) {
      DomString nodeName(child->Name());
      if (nodeName == DomString(u8"line")) {
        ParseSVGLineElement(child);
      }
      else if (nodeName == DomString(u8"rect")) {
        ParseSvgRectElement(child);
      }
      else if (nodeName == DomString(u8"circle")) {
        
      }
      else if (nodeName == DomString(u8"ellipse")) {
        
      }
      else if (nodeName == DomString(u8"polygon")) {

      }
      else if (nodeName == DomString(u8"polyline")) {

      }
      child = child->NextSiblingElement();
    }
    return { true, result };
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
