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

/*
 * DOMString is not normative. Corresponding to w3c standard, DOMString should be implemented as Sequence<char16_t>
 * However, I dislike UTF16. This DOMString is implemented as Utf8 string, interally its data is stored in std::string.
 * All Unicode function is implemented by low level operation system provided function such as MultiByteToWideChar on windows.
 */
class DOMString {
public:
    DOMString(): data_() {

    }

    DOMString(const std::string& data) {
        data_ = data;
    }

    DOMString(const char* data) {
        data_ = data;
    }
    
    DOMString(const char* data, std::size_t buf_size) : data_(data, buf_size) {
        // do nothing
    }

    bool operator==(const DOMString& another);

    std::size_t ChararcterCount() const;

    std::size_t ByteCount() const;

    int CharAt(std::size_t index) const;

    char ByteAt(std::size_t index) const;

    DOMString ToLower() const;

    DOMString ToUpper() const;

private:
    std::string data_;
};

NAMESPACE_END

#endif // TINYSVG_SVG_DOMSTRING_H_