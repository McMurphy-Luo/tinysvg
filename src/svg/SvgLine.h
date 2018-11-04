#ifndef TINYSVG_SVGLINE_H_
#define TINYSVG_SVGLINE_H_

#include "../Config.h"
#include "./SvgBase.h"
#include "./SvgColor.h"

NAMESPACE_BEGIN

class SvgLine
{
public:
  static constexpr SvgType Type = SvgType::Line;

public:
  SvgLine(SvgLength x1, SvgLength x2, SvgLength y1, SvgLength y2, SvgLength border_width)
    : x1_(x1)
    , x2_(x2)
    , y1_(y1)
    , y2_(y2)
    , border_width_(border_width)
  {
    // do nothing
  }

  SvgLine()
    : SvgLine(0, 0, 0, 0, 0)
  {
    // do nothing
  }

  SvgLength X1() const { return x1_; }

  void SetX1(const SvgLength value) { x1_ = value; }

  SvgLength X2() const { return x2_; }

  void SetX2(const SvgLength value) { x2_ = value; }

  SvgLength Y1() const { return y1_; }

  void SetY1(const SvgLength value) { y1_ = value; }

  SvgLength Y2() const { return y2_; }

  void SetY2(const SvgLength value) { y2_ = value; }

  SvgLength BorderWidth() const { return border_width_; }

  void SetBorderWidth(SvgLength value) { border_width_ = value; }

private:
  SvgLength x1_;
  SvgLength x2_;
  SvgLength y1_;
  SvgLength y2_;
  SvgLength border_width_;
};

NAMESPACE_END

#endif // TINYSVG_SVGLINE_H_