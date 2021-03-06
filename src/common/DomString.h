/**
 * @Author McMurphy.Luo
 * @Date 2018-06-05
 * @Description
 * Define an class to help manipulate string since std::string is too weak
 */

#ifndef TINYSVG_DOMSTRING_H_
#define TINYSVG_DOMSTRING_H_

#include "../Config.h"
#include <string>
#include <functional>
#include <vector>
#include <ostream>

NAMESPACE_BEGIN

typedef std::string Utf8String;

Utf8String WideStringToUtf8String(const std::wstring& source);

std::wstring Utf8StringToWideString(const Utf8String& source);

class DomString;

std::ostream& operator<<(std::ostream& target, const DomString& value);

bool operator==(const DomString& lhs, const DomString& rhs);

bool operator!=(const DomString& lhs, const DomString& rhs);

bool operator==(const DomString& lhs, const DomString& rhs);

bool operator>(const DomString& lhs, const DomString& rhs);

bool operator>=(const DomString& lhs, const DomString& rhs);

bool operator<(const DomString& lhs, const DomString& rhs);

bool operator<=(const DomString& lhs, const DomString& rhs);

/*
 * DOMString is not normative. Corresponding to w3c standard, DOMString should be implemented as Sequence<char16_t>
 * However, I dislike UTF16. This DOMString is implemented as Utf8 string, interally its data is stored in std::string.
 * All Unicode function is implemented by operation system provided functions such as MultiByteToWideChar on windows.
 * No Unicode library is required.
 */
class DomString {
  friend std::ostream& operator<<(std::ostream& target, const DomString& value);

  friend bool operator!=(const DomString& lhs, const DomString& rhs);

  friend bool operator==(const DomString& lhs, const DomString& rhs);

  friend bool operator>(const DomString& lhs, const DomString& rhs);

  friend bool operator>=(const DomString& lhs, const DomString& rhs);

  friend bool operator<(const DomString& lhs, const DomString& rhs);

  friend bool operator<=(const DomString& lhs, const DomString& rhs);

public:
  DomString()
    : data_() {
    // do nothing
  }

  DomString(const Utf8String& another)
    : data_(another) {
    // do nothing
  }

  DomString(std::size_t count, char the_char)
    : data_(count, the_char) {
    // do nothing
  }

  DomString(const char* raw_string)
    : data_(raw_string) {
    // do nothing
  }

  DomString(const char* utf8_string_raw, std::size_t buf_size)
    : data_(utf8_string_raw, buf_size) {
    // do nothing
  }

  DomString(const wchar_t* data)
    : data_(WideStringToUtf8String(data)) {
    // do nothing
  }

  DomString(const wchar_t* data, size_t buf_size)
  : data_(WideStringToUtf8String(std::wstring(data, buf_size)))
  {

  }

  operator Utf8String() const { return data_; }

  operator std::wstring() const { return Utf8StringToWideString(data_); }

  std::size_t ChararcterCount() const;

  std::size_t ByteCount() const { return data_.length(); }

  int CharAt(std::size_t index) const;

  char ByteAt(std::size_t index) const { return data_.at(index); }

  bool IsEmpty() const { return data_.empty(); }

  const char* Data() const { return data_.c_str(); }

  void Clear() { data_.clear(); }

  void PushBack(char the_char) { data_.push_back(the_char); }

  DomString Trim() const;

  DomString TrimLeft() const;

  DomString TrimRight() const;

  std::vector<DomString> Split(const DomString& splitter) const;

  DomString Transform(std::function<char(const char&)>) const;

  DomString ToLower() const;

  DomString ToUpper() const;

private:
  Utf8String data_;
};

NAMESPACE_END

#endif // TINYSVG_DOMSTRING_H_