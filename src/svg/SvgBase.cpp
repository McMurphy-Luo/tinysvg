#include "./SvgBase.h"
#include <algorithm>

NAMESPACE_BEGIN

NodeDelegate<nullptr_t> EmptyNode() {
  return NodeDelegate<nullptr_t>(
    std::make_shared<Node<nullptr_t>>(nullptr)
    );
}

NAMESPACE_END