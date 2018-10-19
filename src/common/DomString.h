/**
 * @Author McMurphy.Luo
 * @Date 2018-06-05
 * @Description
 * Define an class to help manipulate string since std::string is too weak
 */

#ifndef TINYSVG_SVG_DOMSTRING_H_
#define TINYSVG_SVG_DOMSTRING_H_

#include "../Config.h"
#include <string>
#include <functional>
#include <vector>

NAMESPACE_BEGIN

typedef std::string Utf8String;

Utf8String WideStringToUtf8String(std::wstring source);

/*
 * DOMString is not normative. Corresponding to w3c standard, DOMString should be implemented as Sequence<char16_t>
 * However, I dislike UTF16. This DOMString is implemented as Utf8 string, interally its data is stored in std::string.
 * All Unicode function is implemented by operation system provided functions such as MultiByteToWideChar on windows.
 * No Unicode library is required.
 */
class DomString {
public:
  DomString()
  : data_() {

  }

  DomString(const Utf8String& another)
  : data_(another) {
    // do nothing
  }

  DomString(const char* utf8_string_raw) : data_(utf8_string_raw) {
    // do nothing
  }

  DomString(const char* utf8_string_raw, std::size_t buf_size) : data_(utf8_string_raw, buf_size) {
    // do nothing
  }

  DomString(const std::wstring& data);

  DomString(const wchar_t* data);

  DomString(const wchar_t* data, std::size_t buf_size);

  bool operator!=(const DomString& another);

  bool operator==(const DomString& another);

  bool operator>(const DomString& another);

  bool operator>=(const DomString& another);

  bool operator<(const DomString& another);

  bool operator<=(const DomString& another);

  std::size_t ChararcterCount() const;

  std::size_t ByteCount() const;

  std::vector<DomString> Split(char the_byte) const;

  std::vector<DomString> Split(int the_character) const;

  int CharAt(std::size_t index) const;

  char ByteAt(std::size_t index) const;

  DomString Transform(std::function<char(const char&)>) const;

  DomString ToLower() const;

  DomString ToUpper() const;

private:
  Utf8String data_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_DOMSTRING_H_