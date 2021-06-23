#pragma once

#include <string>

char* parseInt(long int num);
char* parseFloat(long int num);
bool streq(const char* lhs, const char* rhs);
void parseStr(const char* str, int* size, char** data);

struct String {
    String();
    ~String();
    String(const std::string& str);
    String(const char* str);
    String(const char* str, int len);
    String(const String& str);
    String& operator=(const String& rhs);
    const char* cstr() const;
    operator std::string();
    char operator[](int idx) const;
    bool operator==(const char* rhs);

    char* m_data;
    int m_size;
};
