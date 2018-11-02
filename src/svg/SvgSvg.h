#ifndef TINYSVG_SVGSVG_H_
#define TINYSVG_SVGSVG_H_

#include "../Config.h"
#include <vector>
#include <memory>
#include <optional>
#include "./SvgBase.h"

NAMESPACE_BEGIN

class SvgSvg : public SvgBase {
public:
  struct SvgViewBox {
    optional<SvgLength> x;
    optional<SvgLength> y;
    optional<SvgLength> width;
    optional<SvgLength> height;
  };

public:
  SvgSvg()
  : SvgBase(SvgType::SvgSvg)
  , children_()
  , x_(0)
  , y_(0)
  , width_()
  , height_()
  , view_box_()
  {

  }

  SvgLength X() const { return x_; }

  void SetX(SvgLength value) { x_ = value; }

  SvgLength Y() const { return y_; }

  void SetY(SvgLength value) { y_ = value; }

  optional<SvgLength> Width() const { return width_; }

  void SetWidth(const optional<SvgLength>& value) { width_ = value; }

  optional<SvgLength> Height() const { return height_; }

  void SetHeight(const optional<SvgLength>& value) { height_ = value; }

  optional<SvgViewBox> ViewBox() const { return view_box_; }

  void SetViewBox(const optional<SvgViewBox>& value) { view_box_ = value; }

private:
  SvgLength x_;
  SvgLength y_;
  optional<SvgLength> width_;
  optional<SvgLength> height_;
  optional<SvgViewBox> view_box_;
};

NAMESPACE_END

#endif // TINYSVG_SVGSVG_H_