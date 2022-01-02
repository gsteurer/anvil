#pragma once
#include <string>

#include "anvil/types.h"

namespace anvil {
namespace math {

// CREDIT: The Ray Tracer Challenge - by Jamis Buck

struct Vec4f {
    Vec4f();
    Vec4f(const Vec4f& v);
    Vec4f& operator=(const Vec4f& v);
    Vec4f(f32_t x, f32_t y, f32_t z, f32_t w);
    union {
        struct {
            f32_t x, y, z, w;
        };
        struct {
            f32_t r, g, b, a;
        };
        f32_t raw[4];
    };
};

Vec4f Point(f32_t x, f32_t y, f32_t z);
Vec4f Vector(f32_t x, f32_t y, f32_t z);

bool isPoint(const Vec4f& vec);

bool isVector(const Vec4f& vec);

bool eq(const Vec4f& lhs, const Vec4f& rhs);
bool ne(const Vec4f& lhs, const Vec4f& rhs);

Vec4f add(const Vec4f& lhs, const Vec4f& rhs);

Vec4f sub(const Vec4f& lhs, const Vec4f& rhs);

Vec4f mul(f32_t scale, const Vec4f& vec);
Vec4f mul(const Vec4f& vec, f32_t scale);

Vec4f div(f32_t scale, const Vec4f& vec);
Vec4f div(const Vec4f& vec, f32_t scale);

f32_t mag(const Vec4f& vec);

Vec4f norm(const Vec4f& vec);

f32_t dot(const Vec4f& lhs, const Vec4f& rhs);

Vec4f cross(const Vec4f& lhs, const Vec4f& rhs);

Vec4f operator+(const Vec4f& lhs, const Vec4f& rhs);
Vec4f operator-(const Vec4f& lhs, const Vec4f& rhs);
Vec4f operator*(const Vec4f& lhs, f32_t rhs);
Vec4f operator*(f32_t lhs, const Vec4f& rhs);
bool operator==(const Vec4f& lhs, const Vec4f& rhs);

std::string str(const Vec4f& vec, isize_t precision = 1);

}  // namespace math
}  // namespace anvil