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
using std::dynamic_pointer_cast;
using std::make_shared;
using tinyxml2::XMLDocument;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

namespace { // unamed namespace for this file static staff

  class SvgDocumentParser
  {
  public:
    explicit SvgDocumentParser(XMLDocument* document);

    shared_ptr<SvgSvg> Parse();

  private:
    shared_ptr<SvgBase> ParseElement(XMLElement* element);

    shared_ptr<SvgSvg> ParseSvgElement(XMLElement* element);

    shared_ptr<SvgLine> ParseSvgLineElement(XMLElement* element);

    shared_ptr<SvgRect> ParseSvgRectElement(XMLElement* element);

    shared_ptr<SvgCircle> ParseSvgCircleElement(XMLElement* element);

    shared_ptr<SvgEllipse> ParseSvgEllipseElement(XMLElement* element);

    shared_ptr<SvgPolygon> ParseSvgPolygonElement(XMLElement* element);

    shared_ptr<SvgPolyline> ParseSvgPolylineElement(XMLElement* element);

  private:
    XMLDocument* document_;
  };

  SvgDocumentParser::SvgDocumentParser(XMLDocument* document)
  : document_(document)
  {

  }

  shared_ptr<SvgSvg> SvgDocumentParser::Parse()
  {
    return dynamic_pointer_cast<SvgSvg>(ParseElement(document_->RootElement()));
  }
  
  shared_ptr<SvgBase> SvgDocumentParser::ParseElement(XMLElement* element)
  {
    shared_ptr<SvgBase> graphics;
    DomString nodeName(element->Name());
    if (nodeName == DomString(u8"svg")) {
      graphics = ParseSvgElement(element);
    }
    if (nodeName == DomString(u8"line")) {
      graphics = ParseSvgLineElement(element);
    }
    else if (nodeName == DomString(u8"rect")) {
      graphics = ParseSvgRectElement(element);
    }
    else if (nodeName == DomString(u8"circle")) {
      graphics = ParseSvgCircleElement(element);
    }
    else if (nodeName == DomString(u8"ellipse")) {
      graphics = ParseSvgEllipseElement(element);
    }
    else if (nodeName == DomString(u8"polygon")) {
      graphics = ParseSvgPolygonElement(element);
    }
    else if (nodeName == DomString(u8"polyline")) {
      graphics = ParseSvgPolylineElement(element);
    }
    return graphics;
  }

  shared_ptr<SvgSvg> SvgDocumentParser::ParseSvgElement(XMLElement* element)
  {
    DomString nodeName(element->Name());
    assert(nodeName == DomString(u8"svg"));
    if (nodeName != DomString(u8"svg")) {
      return nullptr;
    }
    SvgSvg result;
    DomString viewBox = DomString(element->Attribute(u8"viewBox"));
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
    return make_shared<SvgSvg>(result);
  }

  shared_ptr<SvgLine> SvgDocumentParser::ParseSvgLineElement(XMLElement* element)
  {
    DomString element_name(element->Name());
    assert(element_name == u8"line");
    SvgLine the_line;
    pair<bool, SvgLength> position_parse_result = ParseNumeric(element->Attribute(u8"x1"));
    if (position_parse_result.first) {
      the_line.SetX1(position_parse_result.second);
    }
    position_parse_result = ParseNumeric(element->Attribute(u8"x2"));
    if (position_parse_result.first) {
      the_line.SetX2(position_parse_result.second);
    }
    position_parse_result = ParseNumeric(element->Attribute(u8"y1"));
    if (position_parse_result.first) {
      the_line.SetY1(position_parse_result.second);
    }
    position_parse_result = ParseNumeric(element->Attribute(u8"y2"));
    if (position_parse_result.first) {
      the_line.SetY2(position_parse_result.second);
    }
    return make_shared<SvgLine>(the_line);
  }

  shared_ptr<SvgRect> SvgDocumentParser::ParseSvgRectElement(XMLElement* element)
  {
    DomString element_name(element->Name());
    assert(element_name == u8"rect");
    SvgRect the_rectangle;
    pair<bool, SvgLength> attribute_parse_result = ParseNumeric(element->Attribute(u8"x"));
    if (attribute_parse_result.first) {
      the_rectangle.SetX(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"y"));
    if (attribute_parse_result.first) {
      the_rectangle.SetY(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"rx"));
    if (attribute_parse_result.first) {
      the_rectangle.SetRX(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"ry"));
    if (attribute_parse_result.first) {
      the_rectangle.SetY(attribute_parse_result.second);
    }
    return make_shared<SvgRect>(the_rectangle);
  }

  shared_ptr<SvgCircle> SvgDocumentParser::ParseSvgCircleElement(XMLElement* element)
  {
    DomString element_name(element->Name());
    assert(element_name == u8"circle");
    SvgCircle the_circle;
    pair<bool, SvgLength> attribute_parse_result = ParseNumeric(element->Attribute(u8"cx"));
    if (attribute_parse_result.first) {
      the_circle.SetCX(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"cy"));
    if (attribute_parse_result.first) {
      the_circle.SetCY(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"r"));
    if (attribute_parse_result.first) {
      the_circle.SetR(attribute_parse_result.second);
    }
    return make_shared<SvgCircle>(the_circle);
  }

  shared_ptr<SvgEllipse> SvgDocumentParser::ParseSvgEllipseElement(XMLElement* element)
  {
    DomString element_name(element->Name());
    assert(element_name == u8"ellipse");
    SvgEllipse the_ellipse;
    pair<bool, SvgLength> attribute_parse_result = ParseNumeric(element->Attribute(u8"cx"));
    if (attribute_parse_result.first) {
      the_ellipse.SetCX(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"cy"));
    if (attribute_parse_result.first) {
      the_ellipse.SetCY(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"rx"));
    if (attribute_parse_result.first) {
      the_ellipse.SetRX(attribute_parse_result.second);
    }
    attribute_parse_result = ParseNumeric(element->Attribute(u8"ry"));
    if (attribute_parse_result.first) {
      the_ellipse.SetRY(attribute_parse_result.second);
    }
    return make_shared<SvgEllipse>(the_ellipse);
  }

  shared_ptr<SvgPolygon> SvgDocumentParser::ParseSvgPolygonElement(XMLElement* element)
  {
    SvgPolygon the_polygon;
    return make_shared<SvgPolygon>(the_polygon);
  }

  shared_ptr<SvgPolyline> SvgDocumentParser::ParseSvgPolylineElement(XMLElement* element)
  {
    SvgPolyline the_polyline;
    return make_shared<SvgPolyline>(the_polyline);
  }

} // end unamed namespace

pair<bool, SvgSvg> Parse(const char* buffer, size_t buffer_size)
{
  tinyxml2::XMLDocument document;
  tinyxml2::XMLError error = document.Parse(buffer, buffer_size);
  if (error != XML_SUCCESS) {
    return make_pair(false, SvgSvg());
  }
  shared_ptr<SvgSvg> result = SvgDocumentParser(&document).Parse();
  if (!result) {
    return make_pair(false, SvgSvg());
  }
  return make_pair(true, *result);
}

NAMESPACE_END
