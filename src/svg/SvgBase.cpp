#include "./SvgBase.h"
#include <algorithm>

using std::find;

NAMESPACE_BEGIN

void SvgBase::AddChild(std::shared_ptr<SvgBase>& target)
{
  if (target->parent_.expired()) {
    
  }
}

void SvgBase::RemoveChild(std::shared_ptr<SvgBase>& child)
{

}

NAMESPACE_END