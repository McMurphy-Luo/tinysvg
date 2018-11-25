#include "./SvgDocument.h"

#include <cassert>
#include "tinyxml2/tinyxml2.h"

#include "../common/DomString.h"
#include "../common/MiscParser.h"
#include "./SvgRect.h"
#include "./SvgLine.h"
#include "./SvgEllipse.h"
#include "./SvgPolygon.h"
#include "./SvgPolyline.h"
#include "./SvgCircle.h"

using std::size_t;
using std::pair;
using std::make_pair;
using std::shared_ptr;
using std::vector;
using std::dynamic_pointer_cast;
using std::make_shared;
using tinyxml2::XMLDocument;
using tinyxml2::XMLError;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

namespace {

  optional<SvgSvg> ParseSvgElement(XMLElement* element)
  {
    DomString nodeName(element->Name());
    assert(nodeName == DomString(u8"svg"));
    if (nodeName != DomString(u8"svg")) {
      return nullopt;
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
    return result;
  }

  optional<SvgLine> ParseSvgLineElement(XMLElement* element)
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
    return the_line;
  }

  optional<SvgRect> ParseSvgRectElement(XMLElement* element)
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
    return the_rectangle;
  }

  optional<SvgCircle> ParseSvgCircleElement(XMLElement* element)
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
    return the_circle;
  }

  optional<SvgEllipse> ParseSvgEllipseElement(XMLElement* element)
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
    return the_ellipse;
  }

  optional<SvgPolygon> ParseSvgPolygonElement(XMLElement* element)
  {
    SvgPolygon the_polygon;
    return the_polygon;
  }

  optional<SvgPolyline> ParseSvgPolylineElement(XMLElement* element)
  {
    SvgPolyline the_polyline;
    return the_polyline;
  }

  template<typename T>
  bool ConstructTree(XMLElement* element, NodeDelegate<T>* parent);

  template<typename T, typename N>
  bool AddChild(XMLElement* element, NodeDelegate<T>* parent_delegate, const optional<N>& should_be_child_value) {
    if (!should_be_child_value.has_value()) {
      return false;
    }
    NodeDelegate<N> me_delegate = parent_delegate->AddChild(should_be_child_value.value());
    XMLElement* child_element = element->FirstChildElement();
    bool child_construction_succeeded = true;
    while (child_element && child_construction_succeeded) {
      child_construction_succeeded = ConstructTree(child_element, &me_delegate);
      child_element = child_element->NextSiblingElement();
    }
    return child_construction_succeeded;
  }

  template<typename T>
  bool ConstructTree(XMLElement* element, NodeDelegate<T>* parent) {
    DomString nodeName(element->Name());
    bool result = false;
    if (nodeName == DomString(u8"svg")) {
      result = AddChild<T, SvgSvg>(element, parent, ParseSvgElement(element));
    }
    else if (nodeName == DomString(u8"line")) {
      result = AddChild<T, SvgLine>(element, parent, ParseSvgLineElement(element));
    }
    else if (nodeName == DomString(u8"rect")) {
      result = AddChild<T, SvgRect>(element, parent, ParseSvgRectElement(element));
    }
    else if (nodeName == DomString(u8"circle")) {
      result = AddChild<T, SvgCircle>(element, parent, ParseSvgCircleElement(element));
    }
    else if (nodeName == DomString(u8"ellipse")) {
      result = AddChild<T, SvgEllipse>(element, parent, ParseSvgEllipseElement(element));
    }
    else if (nodeName == DomString(u8"polygon")) {
      result = AddChild<T, SvgPolygon>(element, parent, ParseSvgPolygonElement(element));
    }
    else if (nodeName == DomString(u8"polyline")) {
      result = AddChild<T, SvgPolyline>(element, parent, ParseSvgPolylineElement(element));
    }
    return result;
  }

} // end unamed namespace


bool SvgDocument::Parse(const DomString& document_string_represent) {
  XMLDocument xml_document;
  xml_document.Parse(document_string_represent.Data(), document_string_represent.ByteCount());
  XMLElement* root_element = xml_document.RootElement();
  optional<SvgSvg> root = ParseSvgElement(root_element);
  bool parse_succeeded = true;
  if (!root.has_value()) {
    parse_succeeded = false;
    return parse_succeeded;
  }
  SetRoot(root.value());
  optional<NodeDelegate<SvgSvg>> root_delegate = Root();
  assert(root_delegate.has_value());
  assert(root_delegate.value().Type() == SvgType::Svg);
  XMLElement* direct_child_of_root = root_element->FirstChildElement();
  while (direct_child_of_root && parse_succeeded) {
    parse_succeeded = ConstructTree(direct_child_of_root, &(root_delegate.value()));
    direct_child_of_root = direct_child_of_root->NextSiblingElement();
  }
  return parse_succeeded;
}

NAMESPACE_END
