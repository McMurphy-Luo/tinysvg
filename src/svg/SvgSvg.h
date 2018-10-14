#ifndef TINYSVG_SVG_SVGSVG_H_
#define TINYSVG_SVG_SVGSVG_H_

#include "../Config.h"
#include "./SVGBase.h"
#include <vector>
#include <memory>

NAMESPACE_BEGIN

class SVGSVG: public SVGBase {
public:
    SVGSVG(): SVGBase(SVGType::SVGSVG), children_() {

    }

    void AddChild(const std::shared_ptr<SVGBase>& target);

    void RemoveChild(const std::shared_ptr<SVGBase>& child);

    std::size_t Length() const;

private:
    std::vector<std::shared_ptr<SVGBase>> children_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_SVGSVG_H_