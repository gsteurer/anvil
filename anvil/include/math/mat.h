#pragma once

#include "math/mat3x3f.h"
#include "math/mat4x4f.h"

template <typename T>
struct matrix_attributes {
    static const unsigned int rows = 0;
    static const unsigned int cols = 0;
};

template <>
struct matrix_attributes<Mat4x4f> {
    static const unsigned int rows = 4;
    static const unsigned int cols = 4;
};

template <>
struct matrix_attributes<Mat3x3f> {
    static const unsigned int rows = 3;
    static const unsigned int cols = 3;
};

template <typename T>
T submatrix(const T& mat, unsigned int row, unsigned int col) {
    T m;
    float data[matrix_attributes<T>::rows * matrix_attributes<T>::cols];
    unsigned int idx = 0;
    for (unsigned int r = 0; r < matrix_attributes<T>::rows; r++) {
        for (unsigned int c = 0; c < matrix_attributes<T>::cols; c++) {
            if (r != row && c != col) {
                data[idx] = mat(r, c);
                idx++;
            }
        }
    }
    idx = 0;
    for (unsigned int r = 0; r < matrix_attributes<T>::rows - 1; r++) {
        for (unsigned int c = 0; c < matrix_attributes<T>::cols - 1; c++) {
            m(r, c) = data[idx];
            idx++;
        }
    }

    return m;
}

template <typename T>
T transpose(const T& mat) {
    T A(mat);
    for (unsigned int n = 0; n <= matrix_attributes<T>::rows - 2; n++) {
        for (unsigned int m = n + 1; m <= matrix_attributes<T>::cols - 1; m++) {
            float tmp = A(n, m);
            A(n, m) = A(m, n);
            A(m, n) = tmp;
        }
    }
    return A;
}
