#ifndef TINYSVG_SVG_SVGSVG_H_
#define TINYSVG_SVG_SVGSVG_H_

#include "../Config.h"
#include "./SvgBase.h"
#include <vector>
#include <memory>

NAMESPACE_BEGIN

class SvgSvg: public SvgBase {
public:
    SvgSvg(): SvgBase(SvgType::SvgSvg), children_() {

    }

    void AddChild(const std::shared_ptr<SvgBase>& target);

    void RemoveChild(const std::shared_ptr<SvgBase>& child);

    std::size_t Length() const;

private:
    std::vector<std::shared_ptr<SvgBase>> children_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGSVG_H_