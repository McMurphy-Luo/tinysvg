#ifndef TINYSVG_SVGDOCUMENT_H_
#define TINYSVG_SVGDOCUMENT_H_

#include "../Config.h"
#include <memory>
#include "./SvgBase.h"

NAMESPACE_BEGIN

template<typename T>
class SvgDocument
{
public:
  explicit SvgDocument()
    : root_node_()
  {

  }

  SvgDocument(const SvgDocument&) = delete;

  SvgDocument& operator=(const SvgDocument&) = delete;

  SvgDocument(SvgDocument&& another)
    : root_node_(std::move(another.root_node_)) {

  }

  SvgDocument& operator=(SvgDocument&& another) {
    root_node_ = std::move(another.root_node_);
  }

  NodeDelegateBase RootNode() const {
    if (!root_node_) {
      return NodeDelegate<SvgNone>();
    }
    return NodeDelegateBase(root_node_);
  }

  void SetRoot(const T& value) {
    if (!root_node_) {
      root_node_ = std::make_shared<Node<T>>(value);
    }
    else {
      *root_node_ = value;
    }
  }

private:
  std::shared_ptr<NodeBase> root_node_;
};

namespace detail {

  template<typename T>
  class SvgDocumentParser
  {
  public:
    explicit SvgDocumentParser(const char* buffer, size_t buffer_size);

    SvgDocument<T> Parse() {
      SvgDocument<T> doc;
      ConstructRootNode(&doc);
      do {
        NodeDelegateBase root_node = doc.RootNode();
        if (!root_node) {
          break;
        }
        optional<NodeDelegate<T>> the_real_root = root.To<T>();
        if (!the_real_root) {
          break;
        }
        doc.SetRoot(the_real_root.value().Value());

        optional<NodeDelegateBase> result_tree = ConstructNode(document_.RootElement(), &root_delegate_);
        if (result_tree.has_value() && result_tree.value().Type() == SvgType::Svg) {
          return result_tree.value().To<T>();
        }
        return nullopt;




      } while (false);
      return doc;
    }

  private:
    template<typename N>
    NodeDelegateBase ConstructNode(XMLElement* element, NodeDelegate<N>* parent) {

    }

    void ConstructRootNode(SvgDocument<T>* doc) {
      XMLElement* root_element = document_.RootElement();
      if (!root_element) {
        return NodeDelegate<SvgNone>();
      }
      DomString node_name(root_element->Name());
      if (node_name != DomString(u8"svg")) {
        return NodeDelegate<SvgNone>();
      }
      optional<T> root_data = ParseSvgElement(root_element);
      if (!root_data) {
        return NodeDelegate<SvgNone>();
      }
      doc->SetRoot(root_data.value());
    }

    template<typename T>
    NodeDelegateBase AddNode(optional<T> target, NodeDelegateBase* parent) {
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
  };

} // namespace detail

template<typename T>
SvgDocument<T> Parse(const char* buffer, std::size_t buffer_size) {
  return detail::SvgDocumentParser<T>(buffer, buffer_size).Parse();
}

NAMESPACE_END

#endif // TINYSVG_SVGDOCUMENT_H_