#pragma once
#include "anvil/types.h"
namespace anvil {
namespace math {

struct Vec3f {
    Vec3f() : x(0.0f), y(0.0f), z(0.0f){};
    Vec3f(const Vec3f& v) : x(v.x), y(v.y), z(v.z){};
    Vec3f(f64_t x, f64_t y, f64_t z) : x(x), y(y), z(z){};
    f64_t x;
    f64_t y;
    f64_t z;
};

}  // namespace math
}  // namespace anvil
