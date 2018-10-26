#ifndef TINYSVG_SVGRECT_H_
#define TINYSVG_SVGRECT_H_

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

  void SetX(SvgLength value) { x_ = value; }

  SvgLength Y() const { return y_; }

  void SetY(SvgLength value) { y_ = value; }

  SvgLength Width() const { return width_; }

  void SetWidth(SvgLength value) { width_ = value; }

  SvgLength Heigth() const { return height_; }

  void SetHeight(SvgLength value) { height_ = value; }

  SvgLength RX() const { return rx_; }

  void SetRX(SvgLength value) { rx_ = value; }

  SvgLength RY() const { return ry_; }

  void SetRY(SvgLength value) { ry_ = value; }

private:
  SvgLength x_;
  SvgLength y_;
  SvgLength width_;
  SvgLength height_;
  SvgLength rx_;
  SvgLength ry_;
};

NAMESPACE_END


#endif // TINYSVG_SVGRECT_H_