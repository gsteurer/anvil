#pragma once
#include "types.h"

namespace anvil {

isize_t strlen(const char* str);
bool streq(const char* lhs, const char* rhs);
char* strrev(const char* str);
void resize(char** buffer, isize_t size);
void strcpy(const char* source, char** destination, isize_t* copied_size);
// void strcat()
//char* substr(const char* str, isize_t start, isize_t end);
//void strcpy(const char* source, char* destination);
//void strncpy(const char* source, char* destination, isize_t size);

char* itoa(i64_t num);
char* ftoa(f64_t num, isize_t precision);

struct String {
    String();
    ~String();
    // String(const std::string& str);
    String(const char* str);
    String(const char* str, isize_t len);
    String(const String& str);
    String& operator=(const String& rhs);
    const char* cstr() const;
    // operator std::string();
    char operator[](isize_t idx) const;
    bool operator==(const char* rhs);

    char* m_data;
    isize_t m_size;
};

}  // namespace anvil