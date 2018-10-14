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

NAMESPACE_BEGIN

typedef std::string utf8string;

/*
 * DOMString is not normative. Corresponding to w3c standard, DOMString should be implemented as Sequence<char16_t>
 * However, I dislike UTF16. This DOMString is implemented as Utf8 string, interally its data is stored in std::string.
 * All Unicode function is implemented by operation system provided functions such as MultiByteToWideChar on windows.
 * No Unicode library is required.
 */
class DOMString {
public:
    DOMString(): data_() {

    }

    DOMString(const utf8string& another): data_(another) {
        // do nothing
    }

    DOMString(const char* utf8_string_raw): data_(utf8_string_raw) {
        // do nothing
    }

    DOMString(const char* utf8_string_raw, std::size_t buf_size) : data_(utf8_string_raw, buf_size) {
        // do nothing
    }

    DOMString(const std::wstring& data);

    DOMString(const wchar_t* data);
    
    DOMString(const wchar_t* data, std::size_t buf_size);

    bool operator==(const DOMString& another);

    bool operator>(const DOMString& another);

    bool operator>=(const DOMString& another);

    bool operator<(const DOMString& another);

    bool operator<=(const DOMString& another);

    std::size_t ChararcterCount() const;

    std::size_t ByteCount() const;

    int CharAt(std::size_t index) const;

    char ByteAt(std::size_t index) const;

    DOMString ToLower() const;

    DOMString ToUpper() const;

private:
    utf8string data_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_DOMSTRING_H_