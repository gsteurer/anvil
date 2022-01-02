#pragma once
#include "anvil/types.h"
namespace anvil {
namespace math {

struct Vec3f {
    Vec3f() : x(0.0f), y(0.0f), z(0.0f){};
    Vec3f(const Vec3f& v) : x(v.x), y(v.y), z(v.z){};
    Vec3f(f32_t x, f32_t y, f32_t z) : x(x), y(y), z(z){};
    f32_t x;
    f32_t y;
    f32_t z;
};

}  // namespace math
}  // namespace anvil
