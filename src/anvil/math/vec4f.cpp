#include "anvil/math/vec4f.h"

#include <iomanip>
#include <sstream>

#include "anvil/math/util.h"
#include "anvil/types.h"

namespace anvil {
namespace math {

Vec4f::Vec4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){};
Vec4f::Vec4f(const Vec4f& v) : x(v.x), y(v.y), z(v.z), w(v.w){};
Vec4f& Vec4f::operator=(const Vec4f& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
    return *this;
}
Vec4f::Vec4f(f32_t x, f32_t y, f32_t z, f32_t w) : x(x), y(y), z(z), w(w){};

Vec4f Point(f32_t x, f32_t y, f32_t z) { return Vec4f(x, y, z, 1.0); }
Vec4f Vector(f32_t x, f32_t y, f32_t z) { return Vec4f(x, y, z, 0.0); }

bool isPoint(const Vec4f& vec) {
    return floateq(1.0, vec.w);
}

bool isVector(const Vec4f& vec) {
    return floateq(0.0, vec.w);
}

bool floateq(const Vec4f& lhs, const Vec4f& rhs) {
    return floateq(lhs.x, rhs.x) &&
           floateq(lhs.y, rhs.y) &&
           floateq(lhs.z, rhs.z) &&
           floateq(lhs.w, rhs.w);
}

bool ne(const Vec4f& lhs, const Vec4f& rhs) {
    return !floateq(lhs, rhs);
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

Vec4f mul(f32_t scale, const Vec4f& vec) {
    return Vec4f(
        scale * vec.x,
        scale * vec.y,
        scale * vec.x,
        scale * vec.w);
}

Vec4f div(f32_t scale, const Vec4f& vec) {
    return Vec4f(
        vec.x / scale,
        vec.y / scale,
        vec.x / scale,
        vec.w / scale);
}

f32_t mag(const Vec4f& vec) {
    return std::sqrt(
        (vec.x * vec.x) +
        (vec.y * vec.y) +
        (vec.z * vec.z) +
        (vec.w * vec.w));
}

Vec4f norm(const Vec4f& vec) {
    f32_t m = mag(vec);
    return Vec4f(
        vec.x / m,
        vec.y / m,
        vec.z / m,
        vec.w / m);
}

f32_t dot(const Vec4f& lhs, const Vec4f& rhs) {
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
Vec4f operator*(const Vec4f& lhs, f32_t rhs) { return Vec4f(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z, rhs * lhs.w); }
Vec4f operator*(f32_t lhs, const Vec4f& rhs) { return rhs * lhs; }
bool operator==(const Vec4f& lhs, const Vec4f& rhs) { return floateq(lhs, rhs); }

Vec4f mul(const Vec4f& vec, f32_t scale) {
    return mul(scale, vec);
}

Vec4f div(const Vec4f& vec, f32_t scale) {
    return div(scale, vec);
}

std::string str(const Vec4f& vec, isize_t precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision)
           << "("
           << vec.x << ", "
           << vec.y << ", "
           << vec.z << ", "
           << vec.w << ")";
    return stream.str();
}

// @@@ implementing data(); info on packing
// https://gcc.gnu.org/onlinedocs/gcc/Structure-Layout-Pragmas.html
// https://stackoverflow.com/questions/45898184/can-i-safely-convert-struct-of-floats-into-float-array-in-c
// https://stackoverflow.com/questions/3318410/pragma-pack-effect

}  // namespace math
}  // namespace anvil