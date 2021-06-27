#pragma once
#include <string>

#include "anvil/math/mat2x2f.h"
#include "anvil/math/vec4f.h"
#include "anvil/types.h"

namespace anvil {
namespace math {

struct Mat4x4f {
    f64_t m_elements[16];
    Mat4x4f();
    Mat4x4f(f64_t* data);
    Mat4x4f(const Mat4x4f& m);
    Mat4x4f& operator=(const Mat4x4f& m);
    f64_t& operator[](isize_t idx);  // change return type to f64_t* to support m[row][col]
    f64_t operator[](isize_t idx) const;
    f64_t& operator()(isize_t row, isize_t col);  // support m(row,col)
    f64_t operator()(isize_t row, isize_t col) const;
};

Mat4x4f Identity();
bool mateq(const Mat4x4f& lhs, const Mat4x4f& rhs);
Mat4x4f mul(const Mat4x4f& mat, f64_t scale);
Mat4x4f mul(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f mul(const Mat4x4f& mat, const Vec4f& vec);
std::string str(const Mat4x4f& m, isize_t precision = 1);
f64_t determinant2x2(const Mat4x4f& mat, isize_t row = 0, isize_t col = 0);
f64_t determinant3x3(const Mat4x4f& mat, isize_t row = 0);
f64_t determinant4x4(const Mat4x4f& mat, isize_t row = 0);
f64_t minor3x3(const Mat4x4f& mat, isize_t row, isize_t col);
f64_t minor4x4(const Mat4x4f& mat, isize_t row, isize_t col);
f64_t cofactor3x3(const Mat4x4f& mat, isize_t row, isize_t col);
f64_t cofactor4x4(const Mat4x4f& mat, isize_t row, isize_t col);
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
