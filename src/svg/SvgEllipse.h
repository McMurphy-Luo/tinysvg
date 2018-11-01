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

  void SetCX(SvgLength value) { cx_ = value; }

  SvgLength CX() const { return cx_; }

  void SetCY(SvgLength value) { cy_ = value; }

  SvgLength CY() const { return cy_; }

private:
  SvgLength cx_;
  SvgLength cy_;
  SvgLength rx_;
  SvgLength ry_;
};

NAMESPACE_END

#endif // TINYSVG_SVGELLIPSE_H_