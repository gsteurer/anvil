#include "anvil/string/string.h"

#include "anvil/string/cstring.h"

namespace anvil {
namespace string {

String::String() {
    m_data = nullptr;
    m_size = 0;
}

String::~String() {
    delete[] m_data;
}

/*
String::String(const std::string& str) : m_data(nullptr), m_size(0) {
    strcpy(str.c_str(), &m_size, &m_data);
}
*/

String::String(const char* str) : m_data(nullptr), m_size(0) {
    strcpy(str, &m_data, &m_size);
}

/*
// @@@ TODO
String::String(const char* str, isize_t len) : m_data(nullptr), m_size(0) {
    strcpy(str, &m_data, &m_size);
}

// @@@ TODO
String::String(const String& str) {
}


// @@@ TODO
String& String::operator=(const String& rhs) {
    return *this;
}
*/

const char* String::cstr() const {
    return m_data;
}

/*
String::operator std::string() {
    return std::string(m_data);
}
*/

char String::operator[](isize_t idx) const {
    if (idx < 0 || idx >= m_size) {
        return '\0';
    }
    return m_data[idx];
}

bool String::operator==(const char* rhs) {
    for (isize_t idx = 0; idx < m_size; idx++) {
        if (m_data[idx] != rhs[idx]) {
            return false;
        }
    }
    return true;
}

}  // namespace string
}  // namespace anvil