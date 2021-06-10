#pragma once
#include <string>

#include "math/mat2x2f.h"
#include "math/vec4f.h"

struct Mat4x4f {
    float m_elements[16];
    Mat4x4f();
    Mat4x4f(float* data);
    Mat4x4f(const Mat4x4f& m);
    Mat4x4f& operator=(const Mat4x4f& m);
    float& operator[](unsigned int idx);  // change return type to float* to support m[row][col]
    const float operator[](unsigned int idx) const;
    float& operator()(unsigned int row, unsigned int col);  // support m(row,col)
    float operator()(unsigned int row, unsigned int col) const;
};

Mat4x4f Identity();
bool eq(const Mat4x4f& lhs, const Mat4x4f& rhs);
Mat4x4f mul(const Mat4x4f& mat, float scale);
Mat4x4f mul(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f mul(const Mat4x4f& mat, const Vec4f& vec);
std::string str(const Mat4x4f& m, unsigned int precision = 1);
float determinant2x2(const Mat4x4f& mat, unsigned int row = 0, unsigned int col = 0);
float determinant3x3(const Mat4x4f& mat, unsigned int row = 0);
float determinant4x4(const Mat4x4f& mat, unsigned int row = 0);
float minor3x3(const Mat4x4f& mat, unsigned int row, unsigned int col);
float minor4x4(const Mat4x4f& mat, unsigned int row, unsigned int col);
float cofactor3x3(const Mat4x4f& mat, unsigned int row, unsigned int col);
float cofactor4x4(const Mat4x4f& mat, unsigned int row, unsigned int col);
// if the determinant of a 4x4 matrix is 0, it is not invertible.
bool invertible(const Mat4x4f& mat);
Mat4x4f inverse(const Mat4x4f& mat);
Mat4x4f round(const Mat4x4f& mat);
bool operator==(const Mat4x4f& lhs, const Mat4x4f& rhs);
bool operator!=(const Mat4x4f& lhs, const Mat4x4f& rhs);
Mat4x4f operator*(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f operator*(const Mat4x4f& mat, const Vec4f& vec);