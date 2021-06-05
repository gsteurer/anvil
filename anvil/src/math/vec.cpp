#include "math/vec.h"
#include "math/util.h"

bool point(Vec4f vec) {
    return eq(1.0, vec.w);
}

bool vector(Vec4f vec) {
    return eq(0.0, vec.w);
}

bool eq(Vec4f lhs, Vec4f rhs) {
    
    return eq(lhs.x, rhs.x) &&
        eq(lhs.y, rhs.y) &&
        eq(lhs.z, rhs.z) &&
        eq(lhs.w, rhs.w);
}

Vec4f add(Vec4f lhs, Vec4f rhs) {
    return Vec4f(
        lhs.x + rhs.x, 
        lhs.y + rhs.y, 
        lhs.z + rhs.z, 
        lhs.w + rhs.w
    );
}

Vec4f sub(Vec4f lhs, Vec4f rhs) {
    return Vec4f( 
        lhs.x - rhs.x, 
        lhs.y - rhs.y, 
        lhs.z - rhs.z, 
        lhs.w - rhs.w
    );
}

Vec4f mul(float scale, Vec4f vec) {
    return Vec4f( 
        scale * vec.x, 
        scale * vec.y, 
        scale * vec.x, 
        scale * vec.w
    );
}

Vec4f div(float scale, Vec4f vec) {
    return Vec4f( 
        vec.x / scale, 
        vec.y / scale, 
        vec.x / scale, 
        vec.w / scale
    );
}

float mag(Vec4f vec) {
    return std::sqrt( 
        (vec.x * vec.x) + 
        (vec.y * vec.y) +
        (vec.z * vec.z) +
        (vec.w * vec.w)
    );
}

Vec4f norm(Vec4f vec) {
    float m = mag(vec);
    return Vec4f( 
        vec.x / m, 
        vec.y / m,
        vec.z / m,
        vec.w / m
    );
}

float dot(Vec4f lhs, Vec4f rhs) {
    return (lhs.x * rhs.x) +
        (lhs.y * rhs.y) + 
        (lhs.z * rhs.z) +
        (lhs.w + rhs.w);
}

Vec4f cross(Vec4f lhs, Vec4f rhs) {
    return Vec4f(
        (lhs.y * rhs.z) - (lhs.z * rhs.y),
        (lhs.z * rhs.x) - (lhs.x * rhs.z),
        (lhs.x * rhs.y) - (lhs.y * rhs.x),
        0.0
    );
}

Vec4f operator+(const Vec4f lhs, const Vec4f rhs) { return add(lhs, rhs); }
Vec4f operator-(const Vec4f lhs, const Vec4f rhs) { return sub(lhs, rhs); }
bool operator==(const Vec4f lhs, const Vec4f rhs) { return eq(lhs, rhs); }

Vec4f mul(Vec4f vec, float scale ) {
    return mul(scale, vec);
}

Vec4f div(Vec4f vec, float scale ) {
    return div(scale, vec);
}
