#pragma once
#include "anvil/types.h"

namespace anvil {
namespace string {

struct String {
    String();
    ~String();
    // String(const std::string& str);
    String(const char* str);
    // @@@ TODO String(const char* str, isize_t len);
    // @@@ TODO String(const String& str);
    // @@@ TODO String& operator=(const String& rhs);
    const char* cstr() const;
    // operator std::string();
    char operator[](isize_t idx) const;
    bool operator==(const char* rhs);

    char* m_data;
    isize_t m_size;
};
}  // namespace string
}  // namespace anvil