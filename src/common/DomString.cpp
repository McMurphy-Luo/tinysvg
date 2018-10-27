#include "./DomString.h"

#include <algorithm>
#include <cassert>
#include <cctype>

#ifdef TINYSVG_WIN32
#include <Windows.h>
#endif

using std::size_t;
using std::transform;
using std::function;
using std::ostream;
using std::wstring;
using std::vector;
using std::isspace;

NAMESPACE_BEGIN

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

wstring Utf8StringToWideString(const Utf8String& source)
{
#ifdef TINYSVG_WIN32
  int size_required = MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, nullptr, 0);
  wchar_t* buffer = new wchar_t[size_required];
  int size_written = MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, buffer, size_required);
  assert(size_written == size_required);
  wstring result(buffer);
  delete[] buffer;
  return result;
#else // TINYSVG_WIN32
  #error "current platform not support by now"
#endif
}

ostream& operator<<(ostream& target, const DomString& value)
{
  return target << value.data_;
}

bool operator==(const DomString& lhs, const DomString& rhs)
{
  return lhs.data_ == rhs.data_;
}

bool operator!=(const DomString& lhs, const DomString& rhs)
{
  return lhs.data_ != rhs.data_;
}

bool operator>(const DomString& lhs, const DomString& rhs)
{
  return lhs.data_ > rhs.data_;
}

bool operator>=(const DomString& lhs, const DomString& rhs)
{
  return lhs.data_ >= rhs.data_;
}

bool operator<(const DomString& lhs, const DomString& rhs)
{
  return lhs.data_ < rhs.data_;
}

bool operator<=(const DomString& lhs, const DomString& rhs)
{
  return lhs.data_ <= rhs.data_;
}

size_t DomString::ChararcterCount() const
{
  return 0;
}

int DomString::CharAt(size_t index) const
{
  return 0;
}

DomString DomString::Trim() const
{
  return TrimLeft().TrimRight();
}

DomString DomString::TrimLeft() const
{
  const char* c_string = Data();
  const char* c_string_end = Data() + ByteCount();
  for (; c_string < c_string_end && isspace(*c_string); ++c_string)
    ;
  return DomString(c_string, c_string_end - c_string);
}

DomString DomString::TrimRight() const
{
  const char* c_string = Data();
  const char* c_string_end = Data() + ByteCount() - 1;
  for (; c_string_end >= c_string && isspace(*c_string_end); --c_string_end)
    ;
  return DomString(c_string, c_string_end - c_string + 1);
}

vector<DomString> DomString::Split(const DomString& splitter) const
{
  vector<DomString> result;
  if (splitter.data_.size() == 0) {
    for (const char& the_char : data_) {
      result.push_back(DomString(1, the_char));
    }
    return result;
  }

  DomString current;
  size_t warden = 0;
  while (warden < data_.size()) {
    size_t look_forward = warden;
    size_t walker = 0;
    while (
      look_forward < data_.size()
      &&
      walker < splitter.data_.size()
      ) {
      if (data_[look_forward] != splitter.data_[walker]) {
        break;
      }
      ++walker;
      ++look_forward;
    }
    if (walker == splitter.data_.size()) {
      result.push_back(current);
      current.Clear();
      warden += walker;
    } else {
      current.PushBack(ByteAt(warden));
      ++warden;
    }
  }
  result.push_back(current);
  return result;
}

DomString DomString::Transform(function<char(const char&)> unary) const
{
  char* buf = new char[data_.length()];
  transform(data_.cbegin(), data_.cend(), buf, unary);
  DomString result(buf, data_.length());
  delete[] buf;
  return result;
}

DomString DomString::ToLower() const
{
  return Transform([](const char& the_char) -> char {
    return tolower(the_char);
  });
}

DomString DomString::ToUpper() const
{
  return Transform([](const char& the_char) -> char {
    return toupper(the_char);
  });
}

NAMESPACE_END