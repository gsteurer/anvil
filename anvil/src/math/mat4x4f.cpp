#include "math/mat4x4f.h"

#include <cstring>
#include <iomanip>
#include <sstream>

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

Mat4x4f transpose(const Mat4x4f& mat) {
    Mat4x4f A(mat);
    for (int n = 0; n <= 2; n++) {
        for (int m = n + 1; m <= 3; m++) {
            float tmp = A(n, m);
            A(n, m) = A(m, n);
            A(m, n) = tmp;
        }
    }
    return A;
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