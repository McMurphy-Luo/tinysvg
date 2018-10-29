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
  SvgSvg()
  : SvgBase(SvgType::SvgSvg)
  , children_()
  , x_(0)
  , y_(0)
  , width_(0)
  , height_(0)
  {

  }

  SvgLength X() const { return x_; }

  void SetX(SvgLength value) { x_ = value; }

  SvgLength Y() const { return y_; }

  void SetY(SvgLength value) { y_ = value; }

  SvgLength Width() const { return width_; }

  void SetWidth(SvgLength value) { width_ = value; }

  SvgLength Height() const { return height_; }

  void SetHeight(SvgLength value) { height_ = value; }

  void AddChild(const std::shared_ptr<SvgBase>& target);

  void RemoveChild(const std::shared_ptr<SvgBase>& child);

private:
  std::vector<std::shared_ptr<SvgBase>> children_;
  SvgLength x_;
  SvgLength y_;
  SvgLength width_;
  SvgLength height_;
};

NAMESPACE_END

#endif // TINYSVG_SVGSVG_H_