#include "./SvgBase.h"
#include <algorithm>

NAMESPACE_BEGIN

void NodeDelegateBase::Detach() {
  if (!the_node_->parent.expired()) {
    std::shared_ptr<NodeBase> parent = the_node_->parent.lock();
    parent->children.erase(
      std::remove(
        parent->children.begin(),
        parent->children.end(),
        the_node_
      ),
      parent->children.end()
    );
  }
}

NAMESPACE_END