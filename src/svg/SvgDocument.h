#ifndef TINYSVG_SVGDOCUMENT_H_
#define TINYSVG_SVGDOCUMENT_H_

#include "../Config.h"
#include <memory>
#include "./SvgBase.h"
#include "./SvgSvg.h"

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

  NodeDelegateBase RootNode() const {
    if (!root_node_) {
      return NodeDelegate<SvgNone>();
    } 
    return NodeDelegateBase(root_node_);
  }

  void SetRoot(const T& value){
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

NAMESPACE_END

#endif // TINYSVG_SVGDOCUMENT_H_