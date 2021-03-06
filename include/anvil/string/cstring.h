#pragma once
#include "anvil/types.h"

namespace anvil {
namespace string {

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

}  // namespace string

}  // namespace anvil