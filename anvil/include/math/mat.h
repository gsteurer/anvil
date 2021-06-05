#pragma once

struct Mat2x2f {
    float e[4];
};

struct Mat4x4f {
    float e[16];
    Mat4x4f();
    float get(unsigned int row, unsigned int col);
};

Mat4x4f Identity();