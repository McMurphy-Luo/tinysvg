#ifndef TINYSVG_SVGLINE_H_
#define TINYSVG_SVGLINE_H_

#include "../Config.h"
#include "./SVGBase.h"

NAMESPACE_BEGIN

class SvgLine : public SvgBase {
public:
  SvgLine(SvgLength x1, SvgLength x2, SvgLength y1, SvgLength y2)
  : SvgBase(SvgType::SvgLine){

  }

  SvgLine()
  : SvgLine(0, 0, 0, 0)
  {

  }

  SvgLength X1() const { return x1_; }

  void SetX1(const SvgLength value) { x1_ = value; }

  SvgLength X2() const { return x2_; }

  void SetX2(const SvgLength value) { x2_ = value; }

  SvgLength Y1() const { return y1_; }

  void SetY1(const SvgLength value) { y1_ = value; }

  SvgLength Y2() const { return y2_; }

  void SetY2(const SvgLength value) { y2_ = value; }

private:
  SvgLength x1_;
  SvgLength x2_;
  SvgLength y1_;
  SvgLength y2_;
};

NAMESPACE_END

#endif // TINYSVG_SVGLINE_H_