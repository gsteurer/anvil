#include "math/mat.h"

#include <cstring>
#include <iomanip>
#include <sstream>

#include "math/util.h"

Mat4x4f::Mat4x4f() {
    for (int idx = 0; idx < 16; idx++) {
        e[idx] = 0.0;
    }
}

Mat4x4f::Mat4x4f(const Mat4x4f& m) {
    for (int idx = 0; idx < 16; idx++) {
        e[idx] = m.e[idx];
    }
}

Mat4x4f Identity() {
    Mat4x4f m;
    m.e[0] = 1.0;
    m.e[5] = 1.0;
    m.e[10] = 1.0;
    m.e[15] = 1.0;
    return m;
}

float& Mat4x4f::operator[](unsigned int idx) {
    return this->e[idx];
}

const float Mat4x4f::operator[](unsigned int idx) const {
    return this->e[idx];
}

float& Mat4x4f::operator()(unsigned int row, unsigned int col) {
    return this->e[(4 * col) + row];
}

float Mat4x4f::operator()(unsigned int row, unsigned int col) const {
    return this->e[(4 * col) + row];
}

Mat4x4f& Mat4x4f::operator=(const Mat4x4f& m) {
    std::memcpy(this->e, m.e, sizeof(float) * 16);
    return *this;
}

bool Mat4x4f::operator==(const Mat4x4f& m) const {
    return eq(*this, m);
}

bool Mat4x4f::operator!=(const Mat4x4f& m) const {
    return !eq(*this, m);
}

bool eq(const Mat4x4f& lhs, const Mat4x4f& rhs) {
    for (int idx = 0; idx < 16; idx++) {
        if (!eq(lhs[idx], rhs[idx])) {
            return false;
        }
    }
    return true;
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