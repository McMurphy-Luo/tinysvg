#include "./SVGDocumentParser.h"
#include <cassert>
#include <tinyxml2/tinyxml2.h>


using std::size_t;
using tinyxml2::XMLDocument;
using tinyxml2::XML_SUCCESS;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

NAMESPACE_BEGIN

SVGDocumentParser::SVGDocumentParser() {
    // do nothing for now
}

SVGSVG SVGDocumentParser::Parse(const char* buffer, size_t buffer_size) {

    tinyxml2::XMLDocument document;
    tinyxml2::XMLError error = document.Parse(buffer, buffer_size);
    if (error != XML_SUCCESS) {
        return SVGSVG();
    }

    XMLElement* root = document.RootElement();
    assert(root->Name() == "SVG");

}

NAMESPACE_END