#include "math/vec4f.h"

#include <iomanip>
#include <sstream>

#include "math/util.h"

Vec4f::Vec4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){};
Vec4f::Vec4f(const Vec4f& v) : x(v.x), y(v.y), z(v.z), w(v.w){};
Vec4f& Vec4f::operator=(const Vec4f& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
    return *this;
}
Vec4f::Vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};

bool point(const Vec4f& vec) {
    return eq(1.0, vec.w);
}

bool vector(const Vec4f& vec) {
    return eq(0.0, vec.w);
}

bool eq(const Vec4f& lhs, const Vec4f& rhs) {
    return eq(lhs.x, rhs.x) &&
           eq(lhs.y, rhs.y) &&
           eq(lhs.z, rhs.z) &&
           eq(lhs.w, rhs.w);
}

bool ne(const Vec4f& lhs, const Vec4f& rhs) {
    return !eq(lhs, rhs);
}

Vec4f add(const Vec4f& lhs, const Vec4f& rhs) {
    return Vec4f(
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w);
}

Vec4f sub(const Vec4f& lhs, const Vec4f& rhs) {
    return Vec4f(
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
        lhs.w - rhs.w);
}

Vec4f mul(float scale, const Vec4f& vec) {
    return Vec4f(
        scale * vec.x,
        scale * vec.y,
        scale * vec.x,
        scale * vec.w);
}

Vec4f div(float scale, const Vec4f& vec) {
    return Vec4f(
        vec.x / scale,
        vec.y / scale,
        vec.x / scale,
        vec.w / scale);
}

float mag(const Vec4f& vec) {
    return std::sqrt(
        (vec.x * vec.x) +
        (vec.y * vec.y) +
        (vec.z * vec.z) +
        (vec.w * vec.w));
}

Vec4f norm(const Vec4f& vec) {
    float m = mag(vec);
    return Vec4f(
        vec.x / m,
        vec.y / m,
        vec.z / m,
        vec.w / m);
}

float dot(const Vec4f& lhs, const Vec4f& rhs) {
    return (lhs.x * rhs.x) +
           (lhs.y * rhs.y) +
           (lhs.z * rhs.z) +
           (lhs.w * rhs.w);
}

Vec4f cross(const Vec4f& lhs, const Vec4f& rhs) {
    return Vec4f(
        (lhs.y * rhs.z) - (lhs.z * rhs.y),
        (lhs.z * rhs.x) - (lhs.x * rhs.z),
        (lhs.x * rhs.y) - (lhs.y * rhs.x),
        0.0);
}

Vec4f operator+(const Vec4f& lhs, const Vec4f& rhs) { return add(lhs, rhs); }
Vec4f operator-(const Vec4f& lhs, const Vec4f& rhs) { return sub(lhs, rhs); }
bool operator==(const Vec4f& lhs, const Vec4f& rhs) { return eq(lhs, rhs); }

Vec4f mul(const Vec4f& vec, float scale) {
    return mul(scale, vec);
}

Vec4f div(const Vec4f& vec, float scale) {
    return div(scale, vec);
}

std::string str(const Vec4f& vec, unsigned int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision)
           << "("
           << vec.x << ", "
           << vec.y << ", "
           << vec.z << ", "
           << vec.w << ")";
    return stream.str();
}
