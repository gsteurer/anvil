#include "string/string.h"

namespace anvil {

isize_t strlen(const char* str) {
    isize_t len = 0;
    char c;
    while ((c = *str++)) {
        len++;
    }
    return len;
}

bool streq(const char* lhs, const char* rhs) {
    char lcurrent;
    char rcurrent;
    while ((lcurrent = *lhs++) && (rcurrent = *rhs++)) {
        if (lcurrent != rcurrent) {
            return false;
        }
    }
    return true;
}

char* strrev(const char* str) {
    isize_t len = strlen(str);
    char* buffer = new char[len + 1];
    isize_t idx = 0;
    for (; idx < len; idx++) {
        buffer[idx] = str[(len - 1) - idx];
    }
    buffer[idx++] = '\0';
    return buffer;
}

void resize(char** buffer, isize_t size) {
    char* previous = *buffer;
    char* position = previous;

    *buffer = new char[size];
    char c;
    isize_t idx = 0;
    while (idx < size && (c = *position++)) {
        (*buffer)[idx++] = c;
    }

    delete[] previous;
}

void strcpy(const char* source, char** destination, isize_t* copied_size) {
    (*copied_size) = 0;
    isize_t buffer_size = 16;
    char* buffer = new char[buffer_size];
    char c;

    while ((c = *source++)) {
        buffer[(*copied_size)++] = c;
        if (*copied_size == buffer_size) {
            buffer_size *= 2;
            resize(&buffer, buffer_size);
        }
    }

    *destination = new char[*copied_size + 1];
    for (isize_t idx = 0; idx < *copied_size; idx++) {
        (*destination)[idx] = buffer[idx];
    }
    (*destination)[*copied_size] = '\0';
    delete[] buffer;
}

char* itoa(i64_t num) {
    isize_t buffer_size = 32;
    char* buffer = new char[buffer_size];

    u64_t value = num;
    bool is_negative = false;
    // @@@ fixme; eliminate the branch
    if (num < 0) {
        value = num * -1;
        is_negative = true;
    }

    isize_t idx = 0;
    u64_t x = value;
    while (x) {
        buffer[idx++] = static_cast<unsigned char>(x % 10 + '0');
        x = x / 10;
        if (idx - 2 == buffer_size) {  // reserve space for sign and null terminator
            buffer_size *= 2;
            resize(&buffer, buffer_size);
        }
    }

    if (is_negative) {
        buffer[idx++] = '-';
    }
    buffer[idx++] = '\0';
    return strrev(buffer);
}

char* ftoa(f64_t num, isize_t precision) {
    isize_t buffer_size = 32;
    char* buffer = new char[buffer_size];
    u64_t pow_n = 10;
    for (isize_t idx = 0; idx < precision; idx++) {
        pow_n *= 10;
    }

    i64_t value = static_cast<i64_t>(num);
    u64_t fraction = static_cast<u64_t>(num - static_cast<f64_t>(value));
    u64_t exponent = static_cast<u64_t>(value);

    itoa(exponent);

    //if (precision > 0) {
    //'.';
    //}
    // @@@ impl strcat
    itoa(fraction);

    return buffer;
}

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

}  // namespace anvil