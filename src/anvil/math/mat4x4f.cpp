#include "anvil/math/mat4x4f.h"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <sstream>

#include "anvil/math/mat.h"
#include "anvil/math/util.h"
#include "anvil/math/vec4f.h"
#include "anvil/types.h"

namespace anvil {
namespace math {

Mat4x4f::Mat4x4f() {
    for (isize_t idx = 0; idx < 16; idx++) {
        m_elements[idx] = 0.0;
    }
}

Mat4x4f::Mat4x4f(const Mat4x4f& m) {
    for (isize_t idx = 0; idx < 16; idx++) {
        m_elements[idx] = m.m_elements[idx];
    }
}

Mat4x4f::Mat4x4f(f32_t* data) {
    for (isize_t idx = 0; idx < 16; idx++) {
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

f32_t& Mat4x4f::operator[](isize_t idx) {
    return this->m_elements[idx];
}

f32_t Mat4x4f::operator[](isize_t idx) const {
    return this->m_elements[idx];
}

f32_t& Mat4x4f::operator()(isize_t row, isize_t col) {
    return this->m_elements[(4 * row) + col];
}

f32_t Mat4x4f::operator()(isize_t row, isize_t col) const {
    return this->m_elements[(4 * row) + col];
}

Mat4x4f& Mat4x4f::operator=(const Mat4x4f& m) {
    std::memcpy(this->m_elements, m.m_elements, sizeof(f32_t) * 16);
    return *this;
}

bool mateq(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    for (isize_t idx = 0; idx < 16; idx++) {
        if (!floateq(lhs[idx], rhs[idx])) {
            return false;
        }
    }
    return true;
}

Mat4x4f mul(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    Mat4x4f m;
    for (isize_t row = 0; row < 4; row++) {
        for (isize_t col = 0; col < 4; col++) {
            m(row, col) = (lhs(row, 0) * rhs(0, col)) +
                          (lhs(row, 1) * rhs(1, col)) +
                          (lhs(row, 2) * rhs(2, col)) +
                          (lhs(row, 3) * rhs(3, col));
        }
    }
    return m;
}

Vec4f mul(const Mat4x4f& mat, const Vec4f& vec) {
    f32_t r[4];
    for (isize_t row = 0; row < 4; row++) {
        Vec4f a(mat(row, 0), mat(row, 1), mat(row, 2), mat(row, 3));
        r[row] = dot(a, vec);
    }
    return Vec4f(r[0], r[1], r[2], r[3]);
}

Mat4x4f mul(const Mat4x4f& mat, f32_t scale) {
    Mat4x4f m;
    for (isize_t row = 0; row < 4; row++) {
        for (isize_t col = 0; col < 4; col++) {
            m(row, col) = mat(row, col) * scale;
        }
    }
    return m;
}

//row, col is top 0,0 of a 2x2 matrix
f32_t determinant2x2(const Mat4x4f& mat, isize_t row, isize_t col) {
    f32_t a = mat(row, col);
    f32_t b = mat(row, col + 1);
    f32_t c = mat(row + 1, col);
    f32_t d = mat(row + 1, col + 1);
    return a * d - b * c;
}

f32_t minor3x3(const Mat4x4f& mat, isize_t row, isize_t col) {
    f32_t data[4];
    isize_t idx = 0;
    for (isize_t r = 0; r < 3; r++) {
        for (isize_t c = 0; c < 3; c++) {
            if (r != row && c != col) {
                data[idx] = mat(r, c);
                idx++;
            }
        }
    }
    return data[0] * data[3] - data[1] * data[2];
}

f32_t cofactor3x3(const Mat4x4f& mat, isize_t row, isize_t col) {
    return ((row + col) & 1) ? -1 * minor3x3(mat, row, col) : minor3x3(mat, row, col);
}

f32_t determinant3x3(const Mat4x4f& mat, isize_t row) {
    f32_t a = cofactor3x3(mat, row, 0);
    f32_t b = cofactor3x3(mat, row, 1);
    f32_t c = cofactor3x3(mat, row, 2);

    return mat(row, 0) * a + mat(row, 1) * b + mat(row, 2) * c;
}

f32_t minor4x4(const Mat4x4f& mat, isize_t row, isize_t col) {
    Mat4x4f m = submatrix<Mat4x4f>(mat, row, col);
    return determinant3x3(m);  // it doesnt matter which row we choose to calculate the determinant from
}

f32_t cofactor4x4(const Mat4x4f& mat, isize_t row, isize_t col) {
    return ((row + col) & 1) ? -1 * minor4x4(mat, row, col) : minor4x4(mat, row, col);
}

f32_t determinant4x4(const Mat4x4f& mat, isize_t row) {
    f32_t det = 0.0;
    for (isize_t c = 0; c < 4; c++) {
        det = det + mat(row, c) * cofactor4x4(mat, row, c);
    }
    return det;
}

bool invertible(const Mat4x4f& mat) {
    return !floateq(determinant4x4(mat), 0.0);
}
Mat4x4f inverse(const Mat4x4f& mat) {
    // create a matrix of cofactors
    // transpose the cofactor matrix
    // divide the transposed matrix by the determinant of the original
    f32_t d = determinant4x4(mat);
    Mat4x4f cofactors;
    for (isize_t row = 0; row < 4; row++) {
        for (isize_t col = 0; col < 4; col++) {
            cofactors(row, col) = cofactor4x4(mat, row, col);
        }
    }
    Mat4x4f t = transpose(Mat4x4f(cofactors));
    return mul(t, 1.0f / d);
}

Mat4x4f matround(const Mat4x4f& mat) {
    Mat4x4f m;
    for (isize_t row = 0; row < 4; row++) {
        for (isize_t col = 0; col < 4; col++) {
            m(row, col) = round(mat(row, col));
        }
    }
    return m;
}

bool operator==(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    return mateq(lhs, rhs);
}

bool operator!=(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    return !mateq(lhs, rhs);
}

Mat4x4f operator*(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    return mul(lhs, rhs);
}

Vec4f operator*(const Mat4x4f& mat, const Vec4f& vec) {
    return mul(mat, vec);
}

std::string str(const Mat4x4f& m, isize_t precision) {
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

}  // namespace math
}  // namespace anvil