#ifndef TINYSVG_SVGELLIPSE_H_
#define TINYSVG_SVGELLIPSE_H_

#include "../Config.h"
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgEllipse
: public SvgBase
{
public:
  SvgEllipse()
  : SvgBase(SvgType::SvgEllipse)
  {

  }
};

NAMESPACE_END

#endif // TINYSVG_SVGELLIPSE_H_