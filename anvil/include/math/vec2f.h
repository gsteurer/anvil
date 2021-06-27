#pragma once

namespace anvil {
namespace math {

struct Vec2f {
    Vec2f() : x(0.0f), y(0.0f){};
    Vec2f(const Vec2f& v) : x(v.x), y(v.y){};
    Vec2f(float x, float y) : x(x), y(y){};
    float x;
    float y;
};

}  // namespace math
}  // namespace anvil