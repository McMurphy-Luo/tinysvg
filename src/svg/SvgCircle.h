#ifndef TINYSVG_SVGCIRCLE_H_
#define TINYSVG_SVGCIRCLE_H_

#include "../Config.h"
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgCircle
{
public:
  SvgCircle(SvgLength cx, SvgLength cy, SvgLength r)
    : cx_(cx)
    , cy_(cy)
    , r_(r)
  {
    // do nothing
  }

  SvgCircle()
    : SvgCircle(0, 0, 0)
  {
    // do nothing
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