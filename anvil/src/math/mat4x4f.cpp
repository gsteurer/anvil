#include "math/mat4x4f.h"

#include <stdio.h>

#include <cstring>
#include <iomanip>
#include <sstream>

#include "math/mat.h"
#include "math/util.h"
#include "math/vec4f.h"

Mat4x4f::Mat4x4f() {
    for (int idx = 0; idx < 16; idx++) {
        m_elements[idx] = 0.0;
    }
}

Mat4x4f::Mat4x4f(const Mat4x4f& m) {
    for (int idx = 0; idx < 16; idx++) {
        m_elements[idx] = m.m_elements[idx];
    }
}

Mat4x4f::Mat4x4f(float* data) {
    for (int idx = 0; idx < 16; idx++) {
        m_elements[idx] = data[idx];
    }
}

Mat4x4f Identity() {
    Mat4x4f m;
    m.m_elements[0] = 1.0;
    m.m_elements[5] = 1.0;
    m.m_elements[10] = 1.0;
    m.m_elements[15] = 1.0;
    return m;
}

float& Mat4x4f::operator[](unsigned int idx) {
    return this->m_elements[idx];
}

const float Mat4x4f::operator[](unsigned int idx) const {
    return this->m_elements[idx];
}

float& Mat4x4f::operator()(unsigned int row, unsigned int col) {
    return this->m_elements[(4 * row) + col];
}

float Mat4x4f::operator()(unsigned int row, unsigned int col) const {
    return this->m_elements[(4 * row) + col];
}

Mat4x4f& Mat4x4f::operator=(const Mat4x4f& m) {
    std::memcpy(this->m_elements, m.m_elements, sizeof(float) * 16);
    return *this;
}

bool eq(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    for (int idx = 0; idx < 16; idx++) {
        if (!eq(lhs[idx], rhs[idx])) {
            return false;
        }
    }
    return true;
}

Mat4x4f mul(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    Mat4x4f m;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m(row, col) = (lhs(row, 0) * rhs(0, col)) +
                          (lhs(row, 1) * rhs(1, col)) +
                          (lhs(row, 2) * rhs(2, col)) +
                          (lhs(row, 3) * rhs(3, col));
        }
    }
    return m;
}

Vec4f mul(const Mat4x4f& mat, const Vec4f& vec) {
    float r[4];
    for (int row = 0; row < 4; row++) {
        Vec4f a(mat(row, 0), mat(row, 1), mat(row, 2), mat(row, 3));
        r[row] = dot(a, vec);
    }
    return Vec4f(r[0], r[1], r[2], r[3]);
}

Mat4x4f mul(const Mat4x4f& mat, float scale) {
    Mat4x4f m;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m(row, col) = mat(row, col) * scale;
        }
    }
    return m;
}

//row, col is top 0,0 of a 2x2 matrix
float determinant2x2(const Mat4x4f& mat, unsigned int row, unsigned int col) {
    float a = mat(row, col);
    float b = mat(row, col + 1);
    float c = mat(row + 1, col);
    float d = mat(row + 1, col + 1);
    return a * d - b * c;
}

float minor3x3(const Mat4x4f& mat, unsigned int row, unsigned int col) {
    float data[4];
    int idx = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (r != row && c != col) {
                data[idx] = mat(r, c);
                idx++;
            }
        }
    }
    return data[0] * data[3] - data[1] * data[2];
}

float cofactor3x3(const Mat4x4f& mat, unsigned int row, unsigned int col) {
    return ((row + col) & 1) ? -1 * minor3x3(mat, row, col) : minor3x3(mat, row, col);
}

float determinant3x3(const Mat4x4f& mat, unsigned int row) {
    float a = cofactor3x3(mat, row, 0);
    float b = cofactor3x3(mat, row, 1);
    float c = cofactor3x3(mat, row, 2);

    return mat(row, 0) * a + mat(row, 1) * b + mat(row, 2) * c;
}

float minor4x4(const Mat4x4f& mat, unsigned int row, unsigned int col) {
    Mat4x4f m = submatrix<Mat4x4f>(mat, row, col);
    return determinant3x3(m);  // it doesnt matter which row we choose to calculate the determinant from
}

float cofactor4x4(const Mat4x4f& mat, unsigned int row, unsigned int col) {
    return ((row + col) & 1) ? -1 * minor4x4(mat, row, col) : minor4x4(mat, row, col);
}

float determinant4x4(const Mat4x4f& mat, unsigned int row) {
    float det = 0.0;
    for (int c = 0; c < 4; c++) {
        det = det + mat(row, c) * cofactor4x4(mat, row, c);
    }
    return det;
}

bool invertible(const Mat4x4f& mat) {
    return !eq(determinant4x4(mat), 0.0);
}
Mat4x4f inverse(const Mat4x4f& mat) {
    // create a matrix of cofactors
    // transpose the cofactor matrix
    // divide the transposed matrix by the determinant of the original
    float d = determinant4x4(mat);
    Mat4x4f cofactors;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            cofactors(row, col) = cofactor4x4(mat, row, col);
        }
    }
    Mat4x4f t = transpose(Mat4x4f(cofactors));
    return mul(t, 1.0 / d);
}

bool operator==(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    return eq(lhs, rhs);
}

bool operator!=(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    return !eq(lhs, rhs);
}

Mat4x4f operator*(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    return mul(lhs, rhs);
}

Vec4f operator*(const Mat4x4f& mat, const Vec4f& vec) {
    return mul(mat, vec);
}

std::string str(const Mat4x4f& m, unsigned int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision)
           << "[\n"
           << "\t" << m(0, 0) << "," << m(0, 1) << "," << m(0, 2) << "," << m(0, 3) << "\n"
           << "\t" << m(1, 0) << "," << m(1, 1) << "," << m(1, 2) << "," << m(1, 3) << "\n"
           << "\t" << m(2, 0) << "," << m(2, 1) << "," << m(2, 2) << "," << m(2, 3) << "\n"
           << "\t" << m(3, 0) << "," << m(3, 1) << "," << m(3, 2) << "," << m(3, 3) << "\n"
           << "]";
    return stream.str();
}
