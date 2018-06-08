#include "./DOMString.h"

#ifdef TINYSVG_WIN32
#include <Windows.h>
#endif

using std::size_t;

NAMESPACE_BEGIN

DOMString::DOMString(const wchar_t* data) {
    
}

DOMString::DOMString(const wchar_t* data, std::size_t buf_size) {

}

bool DOMString::operator==(const DOMString& another) {
    return data_ == another.data_;
}

bool DOMString::operator>(const DOMString& another) {

}

bool DOMString::operator>=(const DOMString& another) {

}

bool DOMString::operator<(const DOMString& another) {
    return data_ < another.data_;
}

bool DOMString::operator<=(const DOMString& another) {
    return data_ <= another.data_;
}

size_t DOMString::ChararcterCount() const {

}

size_t DOMString::ByteCount() const {
    return data_.length();
}

int DOMString::CharAt(size_t index) const {

}

char DOMString::ByteAt(size_t index) const {
    if (index > data_.length())
        return -1;
    return data_.at[index];
}

DOMString DOMString::ToLower() const {

}

DOMString DOMString::ToUpper() const {

}

NAMESPACE_END