#include "string/string.h"

char* parseInt(long int num) {
    char* str = new char;
    return str;
}

char* parseFloat(long int num) {
    char* str = new char;
    return str;
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

void parseStr(const char* str, int* size, char** data) {
    (*size) = 0;
    if (*data != nullptr) {
        delete[](*data);
    }
    int buffer_size = 16;
    char* buffer = new char[buffer_size];
    char c;
    while ((c = *str++)) {
        buffer[*size] = c;
        (*size)++;
        if (*size == buffer_size) {
            char* previous = buffer;
            buffer_size *= 2;
            buffer = new char[buffer_size];
            for (int jdx = 0; jdx < *size; jdx++) {
                buffer[jdx] = previous[jdx];
            }
            delete[] previous;
        }
    }

    *data = new char[*size + 1];
    for (int idx = 0; idx < *size; idx++) {
        (*data)[idx] = buffer[idx];
    }
    (*data)[*size] = '\0';
    delete[] buffer;
}

String::String() {
    m_data = nullptr;
    m_size = 0;
}

String::~String() {
    delete[] m_data;
}

String::String(const std::string& str) : m_data(nullptr), m_size(0) {
    parseStr(str.c_str(), &m_size, &m_data);
}

String::String(const char* str) : m_data(nullptr), m_size(0) {
    parseStr(str, &m_size, &m_data);
}

String::String(const char* str, int len) : m_data(nullptr), m_size(0) {
    parseStr(str, &m_size, &m_data);
}

String::String(const String& str) {
}

String& String::operator=(const String& rhs) {
    return *this;
}

const char* String::cstr() const {
    return m_data;
}

String::operator std::string() {
    return std::string(m_data);
}

char String::operator[](int idx) const {
    if (idx < 0 || idx >= m_size) {
        return '\0';
    }
    return m_data[idx];
}

bool String::operator==(const char* rhs) {
    for (int idx = 0; idx < m_size; idx++) {
        if (m_data[idx] != rhs[idx]) {
            return false;
        }
    }
    return true;
}
