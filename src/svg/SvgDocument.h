#ifndef TINYSVG_SVGDOCUMENT_H_
#define TINYSVG_SVGDOCUMENT_H_

#include "../Config.h"
#include <memory>
#include "../common/DomString.h"
#include "./SvgBase.h"
#include "./SvgSvg.h"

NAMESPACE_BEGIN

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
    : root_node_(std::move(another.root_node_)){

  }

  SvgDocument& operator=(SvgDocument&& another) {
    root_node_ = std::move(another.root_node_);
  }

  optional<NodeDelegate<SvgSvg>> Root() const {
    if (!root_node_) {
      return make_optional<NodeDelegate<SvgSvg>>();
    }
    return make_optional<NodeDelegate<SvgSvg>>(NodeDelegate<SvgSvg>(root_node_));
  }

  void SetRoot(const SvgSvg& value) {
    if (!root_node_) {
      root_node_ = std::make_shared<Node<SvgSvg>>(value);
    }
    else {
      root_node_->Value() = value;
    }
  }

private:
  std::shared_ptr<Node<SvgSvg>> root_node_;
};

SvgDocument Parse(const DomString& document_string_represent);

NAMESPACE_END

#endif // TINYSVG_SVGDOCUMENT_H_