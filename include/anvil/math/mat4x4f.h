#pragma once
#include <string>

#include "anvil/math/mat2x2f.h"
#include "anvil/math/vec4f.h"
#include "anvil/types.h"

namespace anvil {
namespace math {

// CREDIT: The Ray Tracer Challenge - by Jamis Buck

struct Mat4x4f {
    union {
        f32_t m_elements[16];
        struct {
            Vec4f a, b, c, d;
        };
    };
    Mat4x4f();
    Mat4x4f(f32_t* data);
    Mat4x4f(const Mat4x4f& m);
    Mat4x4f& operator=(const Mat4x4f& m);
    f32_t& operator[](isize_t idx);  // change return type to f32_t* to support m[row][col]
    f32_t operator[](isize_t idx) const;
    f32_t& operator()(isize_t row, isize_t col);  // support m(row,col)
    f32_t operator()(isize_t row, isize_t col) const;
};

Mat4x4f Identity();
Mat4x4f Translate(f32_t x, f32_t y, f32_t z);
Mat4x4f Scale(f32_t x, f32_t y, f32_t z);
Mat4x4f RotateX(f32_t radians);
Mat4x4f RotateY(f32_t radians);
Mat4x4f RotateZ(f32_t radians);
Mat4x4f Shear(f32_t xy, f32_t xz, f32_t yx, f32_t yz, f32_t zx, f32_t zy);
bool mateq(const Mat4x4f& lhs, const Mat4x4f& rhs);
Mat4x4f mul(const Mat4x4f& mat, f32_t scale);
Mat4x4f mul(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f mul(const Mat4x4f& mat, const Vec4f& vec);
std::string str(const Mat4x4f& m, isize_t precision = 1);
f32_t determinant2x2(const Mat4x4f& mat, isize_t row = 0, isize_t col = 0);
f32_t determinant3x3(const Mat4x4f& mat, isize_t row = 0);
f32_t determinant4x4(const Mat4x4f& mat, isize_t row = 0);
f32_t minor3x3(const Mat4x4f& mat, isize_t row, isize_t col);
f32_t minor4x4(const Mat4x4f& mat, isize_t row, isize_t col);
f32_t cofactor3x3(const Mat4x4f& mat, isize_t row, isize_t col);
f32_t cofactor4x4(const Mat4x4f& mat, isize_t row, isize_t col);
// if the determinant of a 4x4 matrix is 0, it is not invertible.
bool invertible(const Mat4x4f& mat);
Mat4x4f inverse(const Mat4x4f& mat);
Mat4x4f matround(const Mat4x4f& mat);
bool operator==(const Mat4x4f& lhs, const Mat4x4f& rhs);
bool operator!=(const Mat4x4f& lhs, const Mat4x4f& rhs);
Mat4x4f operator*(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f operator*(const Mat4x4f& mat, const Vec4f& vec);

}  // namespace math
}  // namespace anvil
