#ifndef TINYSVG_SVGELLIPSE_H_
#define TINYSVG_SVGELLIPSE_H_

#include "../Config.h"
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgEllipse
{
public:
  static constexpr SvgType Type = SvgType::Ellipse;

public:
  SvgEllipse(SvgLength cx, SvgLength cy, SvgLength rx, SvgLength ry) {

  }

  SvgEllipse()
    : SvgEllipse(0, 0, 0, 0) {

  }

  void SetCX(SvgLength value) { cx_ = value; }

  SvgLength CX() const { return cx_; }

  void SetCY(SvgLength value) { cy_ = value; }

  SvgLength CY() const { return cy_; }

  void SetRX(SvgLength value) { rx_ = value; }

  SvgLength RX() const { return rx_; }

  void SetRY(SvgLength value) { ry_ = value; }

  SvgLength RY() const { return ry_; }

private:
  SvgLength cx_;
  SvgLength cy_;
  SvgLength rx_;
  SvgLength ry_;
};

NAMESPACE_END

#endif // TINYSVG_SVGELLIPSE_H_