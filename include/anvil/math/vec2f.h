#pragma once
#include "anvil/types.h"
namespace anvil {
namespace math {

struct Vec2f {
    Vec2f() : x(0.0f), y(0.0f){};
    Vec2f(const Vec2f& v) : x(v.x), y(v.y){};
    Vec2f(f32_t x, f32_t y) : x(x), y(y){};
    f32_t x;
    f32_t y;
};

}  // namespace math
}  // namespace anvil