#pragma once

struct Vec3f {
    Vec3f() : x(0.0f), y(0.0f), z(0.0f){};
    Vec3f(const Vec3f& v) : x(v.x), y(v.y), z(v.z){};
    Vec3f(float x, float y, float z) : x(x), y(y), z(z){};
    float x;
    float y;
    float z;
};
