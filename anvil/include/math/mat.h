#pragma once

struct Mat2x2f {
    float e[4];
};

struct Mat4x4f {
    float e[16];
    Mat4x4f() { 
        for (int idx = 0; idx < 16; idx++) {
            e[idx] = 0.0;
        }
    };
    float get(unsigned int row, unsigned int col) { return this->e[(4 * col) + row]; };
};

Mat4x4f Identity() {
    Mat4x4f m;
    m.e[0] = 1.0;
    m.e[5] = 1.0;
    m.e[10] = 1.0;
    m.e[15] = 1.0;
    return m;
}