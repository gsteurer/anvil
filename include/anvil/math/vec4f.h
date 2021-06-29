#pragma once
#include <string>

#include "anvil/types.h"

namespace anvil {
namespace math {

struct Vec4f {
    Vec4f();
    Vec4f(const Vec4f& v);
    Vec4f& operator=(const Vec4f& v);
    Vec4f(f64_t x, f64_t y, f64_t z, f64_t w);
    f64_t x;
    f64_t y;
    f64_t z;
    f64_t w;
};

bool point(const Vec4f& vec);

bool vector(const Vec4f& vec);

bool eq(const Vec4f& lhs, const Vec4f& rhs);
bool ne(const Vec4f& lhs, const Vec4f& rhs);

Vec4f add(const Vec4f& lhs, const Vec4f& rhs);

Vec4f sub(const Vec4f& lhs, const Vec4f& rhs);

Vec4f mul(f64_t scale, const Vec4f& vec);
Vec4f mul(const Vec4f& vec, f64_t scale);

Vec4f div(f64_t scale, const Vec4f& vec);
Vec4f div(const Vec4f& vec, f64_t scale);

f64_t mag(const Vec4f& vec);

Vec4f norm(const Vec4f& vec);

f64_t dot(const Vec4f& lhs, const Vec4f& rhs);

Vec4f cross(const Vec4f& lhs, const Vec4f& rhs);

Vec4f operator+(const Vec4f& lhs, const Vec4f& rhs);
Vec4f operator-(const Vec4f& lhs, const Vec4f& rhs);
bool operator==(const Vec4f& lhs, const Vec4f& rhs);

std::string str(const Vec4f& vec, isize_t precision = 1);

}  // namespace math
}  // namespace anvil