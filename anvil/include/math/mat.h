#pragma once
#include <string>

#include "math/vec.h"

struct Mat2x2f {
    float e[4];
};

struct Mat4x4f {
    float e[16];
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
Mat4x4f mul(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f mul(const Mat4x4f& mat, const Vec4f& vec);
Mat4x4f transpose(const Mat4x4f& mat);
std::string str(const Mat4x4f& m, unsigned int precision = 1);

bool operator==(const Mat4x4f& lhs, const Mat4x4f& rhs);
bool operator!=(const Mat4x4f& lhs, const Mat4x4f& rhs);
Mat4x4f operator*(const Mat4x4f& lhs, const Mat4x4f& rhs);
Vec4f operator*(const Mat4x4f& mat, const Vec4f& vec);