#include "math/mat.h"
#include "math/util.h"

Mat4x4f::Mat4x4f() { 
    for (int idx = 0; idx < 16; idx++) {
        e[idx] = 0.0;
    }
}

float Mat4x4f::get(unsigned int row, unsigned int col) { return this->e[(4 * col) + row]; };

Mat4x4f Identity() {
    Mat4x4f m;
    m.e[0] = 1.0;
    m.e[5] = 1.0;
    m.e[10] = 1.0;
    m.e[15] = 1.0;
    return m;
}