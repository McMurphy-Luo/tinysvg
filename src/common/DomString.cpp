#include "./DomString.h"
#include <algorithm>

#ifdef TINYSVG_WIN32
#include <Windows.h>
#endif

using std::size_t;

NAMESPACE_BEGIN

DomString::DomString(const wchar_t* data) {
    
}

DomString::DomString(const wchar_t* data, std::size_t buf_size) {

}

bool DomString::operator==(const DomString& another) {
    return data_ == another.data_;
}

bool DomString::operator>(const DomString& another) {
  return true;
}

bool DomString::operator>=(const DomString& another) {
  return true;
}

bool DomString::operator<(const DomString& another) {
    return data_ < another.data_;
}

bool DomString::operator<=(const DomString& another) {
    return data_ <= another.data_;
}

size_t DomString::ChararcterCount() const {
  return 0;
}

size_t DomString::ByteCount() const {
    return data_.length();
}

int DomString::CharAt(size_t index) const {
  return 0;
}

char DomString::ByteAt(size_t index) const {
    return data_.at(index);
}

DomString DomString::Transform(std::function<char(const char&)> unary) const {
  char* buf = new char[data_.length()];
  std::transform(data_.cbegin(), data_.cend(), buf, unary);
  DomString result(buf, data_.length());
  delete[] buf;
  return result;
}

DomString DomString::ToLower() const {
  return Transform([](const char& the_char) -> char {
    return tolower(the_char);
  });
}

DomString DomString::ToUpper() const {
  return Transform([](const char& the_char) -> char {
    return toupper(the_char);
  });
}

NAMESPACE_END