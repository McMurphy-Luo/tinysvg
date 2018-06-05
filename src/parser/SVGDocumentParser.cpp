#include "./SVGDocumentParser.h"
#include <cassert>
#include "../tinyxml2/tinyxml2.h"
#include "../svg/DOMString.h"

using std::size_t;
using std::pair;
using std::make_pair;
using tinyxml2::XMLDocument;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

SVGDocumentParser::SVGDocumentParser() {
    // do nothing for now
}

pair<bool, SVGSVG> SVGDocumentParser::Parse(const char* buffer, size_t buffer_size) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLError error = document.Parse(buffer, buffer_size);
    if (error != XML_SUCCESS) {
        return make_pair(false, SVGSVG());
    }
    XMLElement* root = document.RootElement();
    DOMString nodeName(root->Name());
    if (nodeName.ToLower != "svg") {
        return make_pair(false, SVGSVG());
    }
    const char* viewBox = root->Attribute("viewBox");
    if (root->NoChildren()) {
        return make_pair(true, SVGSVG());
    }

}

NAMESPACE_END