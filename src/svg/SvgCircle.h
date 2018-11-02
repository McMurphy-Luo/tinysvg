#ifndef TINYSVG_SVGCIRCLE_H_
#define TINYSVG_SVGCIRCLE_H_

#include "../Config.h"
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgCircle:
public SvgBase
{
public:
  SvgCircle()
  : SvgBase(SvgType::SvgCircle)
  , cx_(0)
  , cy_(0)
  , r_(0)
  {

  }

  SvgLength CX() const { return cx_; }

  void SetCX(SvgLength value) { cx_ = value; }

  SvgLength CY() const { return cy_; }

  void SetCY(SvgLength value) { cy_ = value; }

  SvgLength R() const { return r_; }

  void SetR(SvgLength value) { r_ = value; }

private:
  SvgLength cx_;
  SvgLength cy_;
  SvgLength r_;
};

NAMESPACE_END


#endif // TINYSVG_SVGCIRCLE_H_