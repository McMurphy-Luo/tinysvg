#ifndef TINYSVG_SVGDOCUMENT_H_
#define TINYSVG_SVGDOCUMENT_H_

#include "../Config.h"
#include <memory>
#include "./SvgBase.h"
#include "./SvgSvg.h"

NAMESPACE_BEGIN

class SvgDocument
{
public:
  SvgDocument()
    : root_node_()
  {

  }

  SvgDocument(const SvgDocument&) = delete;

  SvgDocument& operator=(const SvgDocument&) = delete;

  NodeDelegateBase RootNode() const { if (!root_node_) return NodeDelegate<SvgNone>(); }

private:
  std::shared_ptr<Node<SvgSvg>> root_node_;
};

NAMESPACE_END

#endif // TINYSVG_SVGDOCUMENT_H_