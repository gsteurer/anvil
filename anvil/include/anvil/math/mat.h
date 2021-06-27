#pragma once

#include "anvil/math/mat3x3f.h"
#include "anvil/math/mat4x4f.h"

namespace anvil {
namespace math {

template <typename T>
struct matrix_attributes {
    static const isize_t rows = 0;
    static const isize_t cols = 0;
};

template <>
struct matrix_attributes<Mat4x4f> {
    static const isize_t rows = 4;
    static const isize_t cols = 4;
};

template <>
struct matrix_attributes<Mat3x3f> {
    static const isize_t rows = 3;
    static const isize_t cols = 3;
};

template <typename T>
T submatrix(const T& mat, isize_t row, isize_t col) {
    T m;
    f64_t data[matrix_attributes<T>::rows * matrix_attributes<T>::cols];
    isize_t idx = 0;
    for (isize_t r = 0; r < matrix_attributes<T>::rows; r++) {
        for (isize_t c = 0; c < matrix_attributes<T>::cols; c++) {
            if (r != row && c != col) {
                data[idx] = mat(r, c);
                idx++;
            }
        }
    }
    idx = 0;
    for (isize_t r = 0; r < matrix_attributes<T>::rows - 1; r++) {
        for (isize_t c = 0; c < matrix_attributes<T>::cols - 1; c++) {
            m(r, c) = data[idx];
            idx++;
        }
    }

    return m;
}

template <typename T>
T transpose(const T& mat) {
    T A(mat);
    for (isize_t n = 0; n <= matrix_attributes<T>::rows - 2; n++) {
        for (isize_t m = n + 1; m <= matrix_attributes<T>::cols - 1; m++) {
            f64_t tmp = A(n, m);
            A(n, m) = A(m, n);
            A(m, n) = tmp;
        }
    }
    return A;
}

}  // namespace math
}  // namespace anvil