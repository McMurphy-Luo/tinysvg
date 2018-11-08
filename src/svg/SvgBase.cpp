#include "./SvgBase.h"
#include <algorithm>

using std::shared_ptr;
using std::remove;

NAMESPACE_BEGIN

void NodeDelegateBase::Detach() {
  if (!the_node_->parent.expired()) {
    shared_ptr<NodeBase> parent = the_node_->parent.lock();
    parent->children.erase(
      remove(
        parent->children.begin(),
        parent->children.end(),
        the_node_
      ),
      parent->children.end()
    );
  }
}

NAMESPACE_END