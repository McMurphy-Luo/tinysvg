#include "./DOMString.h"

using std::size_t;

NAMESPACE_BEGIN

bool DOMString::operator==(const DOMString& another) {
    return data_ == another.data_;
}

size_t DOMString::ChararcterCount() const {

}

size_t DOMString::ByteCount() const {

}

int DOMString::CharAt(size_t index) const {

}

char DOMString::ByteAt(size_t index) const {

}

DOMString DOMString::ToLower() const {

}

DOMString DOMString::ToUpper() const {

}

NAMESPACE_END