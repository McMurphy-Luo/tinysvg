#include "./DomString.h"
#include <algorithm>
#include <cassert>

#ifdef TINYSVG_WIN32
#include <Windows.h>
#endif

using std::size_t;
using std::transform;
using std::function;
using std::wstring;
using std::vector;

NAMESPACE_BEGIN

Utf8String WideStringToUtf8String(const wchar_t* data) {
  return WideStringToUtf8String(data);
}

Utf8String WideStringToUtf8String(const wstring& source)
{
#ifdef TINYSVG_WIN32
  int size_required = WideCharToMultiByte(CP_UTF8, 0, source.c_str(), -1, nullptr, 0, nullptr, nullptr);
  char* buffer = new char[size_required];
  int size_written = WideCharToMultiByte(CP_UTF8, 0, source.c_str(), -1, buffer, size_required, nullptr, nullptr);
  assert(size_written == size_required);
  Utf8String result(buffer);
  delete[] buffer;
  return result;
#else // TINYSVG_WIN32
  #error "current platform not support by now"
#endif
}

DomString::DomString(const wchar_t* data)
: data_(WideStringToUtf8String(data))
{

}

DomString::DomString(const wchar_t* data, size_t buf_size) {

}

bool DomString::operator==(const DomString& another) {
    return data_ == another.data_;
}

bool DomString::operator!=(const DomString& another) {
  return data_ != another.data_;
}

bool DomString::operator>(const DomString& another) {
  return data_ > another.data_;
}

bool DomString::operator>=(const DomString& another) {
  return data_ >= another.data_;
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

vector<DomString> DomString::Split() const {

  


  return vector<DomString>();
}

DomString DomString::Transform(function<char(const char&)> unary) const {
  char* buf = new char[data_.length()];
  transform(data_.cbegin(), data_.cend(), buf, unary);
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