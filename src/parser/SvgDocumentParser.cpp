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
using tinyxml2::XMLError;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

namespace { // unamed namespace for this file static staff

  class SvgDocumentParser
  {
  public:
    explicit SvgDocumentParser(const char* buffer, size_t buffer_size);

    optional<NodeDelegate<SvgSvg>> Parse();

  private:
    optional<NodeDelegateBase> ConstructNode(XMLElement* element, NodeDelegateBase* parent);

    template<typename T>
    optional<NodeDelegateBase> AddNode(optional<T> target, NodeDelegateBase* parent) {
      if (target.has_value()) {
        return parent->AddChild(target.value());
      }
      return nullopt;
    }

    optional<SvgSvg> ParseSvgElement(XMLElement* element);

    optional<SvgLine> ParseSvgLineElement(XMLElement* element);

    optional<SvgRect> ParseSvgRectElement(XMLElement* element);

    optional<SvgCircle> ParseSvgCircleElement(XMLElement* element);

    optional<SvgEllipse> ParseSvgEllipseElement(XMLElement* element);

    optional<SvgPolygon> ParseSvgPolygonElement(XMLElement* element);

    optional<SvgPolyline> ParseSvgPolylineElement(XMLElement* element);

  private:
    XMLDocument document_;
    XMLError error_;
    SvgDocument<SvgSvg> svg_doc_;
  };

  SvgDocumentParser::SvgDocumentParser(const char* buffer, size_t buffer_size)
    : document_()
    , error_(XML_SUCCESS)
    , svg_doc_()
  {
    error_ = document_.Parse(buffer, buffer_size);
  }

  optional<NodeDelegate<SvgSvg>> SvgDocumentParser::Parse() {
    optional<NodeDelegateBase> result_tree = ConstructNode(document_.RootElement(), &root_delegate_);
    if (result_tree.has_value() && result_tree.value().Type() == SvgType::Svg) {
      return result_tree.value().To<SvgSvg>();
    }
    return nullopt;
  }

  optional<NodeDelegateBase> SvgDocumentParser::ConstructNode(XMLElement* element, NodeDelegateBase* parent) {
    DomString nodeName(element->Name());
    optional<NodeDelegateBase> me;
    if (nodeName == DomString(u8"svg")) {
      me = AddNode<SvgSvg>(ParseSvgElement(element), parent);
    }
    else if (nodeName == DomString(u8"line")) {
      me = AddNode<SvgLine>(ParseSvgLineElement(element), parent);
    }
    else if (nodeName == DomString(u8"rect")) {
      me = AddNode<SvgRect>(ParseSvgRectElement(element), parent);
    }
    else if (nodeName == DomString(u8"circle")) {
      me = AddNode<SvgCircle>(ParseSvgCircleElement(element), parent);
    }
    else if (nodeName == DomString(u8"ellipse")) {
      me = AddNode<SvgEllipse>(ParseSvgEllipseElement(element), parent);
    }
    else if (nodeName == DomString(u8"polygon")) {
      me = AddNode<SvgPolygon>(ParseSvgPolygonElement(element), parent);
    }
    else if (nodeName == DomString(u8"polyline")) {
      me = AddNode<SvgPolyline>(ParseSvgPolylineElement(element), parent);
    }
    return me;
  }

  optional<SvgSvg> SvgDocumentParser::ParseSvgElement(XMLElement* element)
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

  optional<SvgLine> SvgDocumentParser::ParseSvgLineElement(XMLElement* element)
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

  optional<SvgRect> SvgDocumentParser::ParseSvgRectElement(XMLElement* element)
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

  optional<SvgCircle> SvgDocumentParser::ParseSvgCircleElement(XMLElement* element)
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

  optional<SvgEllipse> SvgDocumentParser::ParseSvgEllipseElement(XMLElement* element)
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

  optional<SvgPolygon> SvgDocumentParser::ParseSvgPolygonElement(XMLElement* element)
  {
    SvgPolygon the_polygon;
    return the_polygon;
  }

  optional<SvgPolyline> SvgDocumentParser::ParseSvgPolylineElement(XMLElement* element)
  {
    SvgPolyline the_polyline;
    return the_polyline;
  }

} // end unamed namespace

optional<NodeDelegate<SvgSvg>> Parse(const char* buffer, size_t buffer_size)
{
  return SvgDocumentParser(buffer, buffer_size).Parse();
}

NAMESPACE_END
