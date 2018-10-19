#ifndef TINYSVG_SVG_SVGRECT_H_
#define TINYSVG_SVG_SVGRECT_H_

#include "../Config.h"
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgRect : public SvgBase {
public:
  SvgRect(SvgLength x, SvgLength y, SvgLength width, SvgLength height, SvgLength rx, SvgLength ry)
    :SvgBase(SvgType::SvgRectangle),
    x_(x),
    y_(y),
    width_(width),
    height_(height),
    rx_(rx),
    ry_(ry)
  {

  }

  SvgRect()
    : SvgRect(0, 0, 0, 0, 0, 0)
  {

  }

  SvgLength X() const { return x_; }

  void SetX(SVGLength value) { x_ = value; }

  SVGLength Y() const { return y_; }

  void SetY(SVGLength value) { y_ = value; }

  SVGLength Width() const { return width_; }

  void SetWidth(SVGLength value) { width_ = value; }

  SVGLength Heigth() const { return height_; }

  void SetHeight(SVGLength value) { height_ = value; }

  SVGLength RX() const { return rx_; }

  void SetRX(SVGLength value) { rx_ = value; }

  SVGLength RY() const { return ry_; }

  void SetRY(SVGLength value) { ry_ = value; }

private:
  SVGLength x_;
  SVGLength y_;
  SVGLength width_;
  SVGLength height_;
  SVGLength rx_;
  SVGLength ry_;
};

NAMESPACE_END


#endif // TINYSVG_SVG_SVGRECT_H_