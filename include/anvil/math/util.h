#pragma once
#include <cmath>

#include "anvil/types.h"

namespace anvil {
namespace math {

#define PI 3.14159265358979323846f

inline f32_t radians(f32_t degrees) {
    return degrees / 180.0 * PI;
}

inline bool floateq(f32_t lhs, f32_t rhs) {
    return std::fabs(lhs - rhs) < std::numeric_limits<float>::epsilon();
}
/*
inline anvil::i64_t abs(anvil::i64_t n) {
    //anvil::i64_t v;
    //anvil::u64_t r;
    // http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
    //anvil::i64_t const mask = v >> sizeof(anvil::i64_t) * CHAR_BIT - 1;
    //r = (v + mask) ^ mask;
    // @@@ finish me
    
        unsigned long temp = key >> (sizeof(int) * 8 - 1);
        key ^= temp;
        key += temp & 1;
    
return 0;
}
*/
}  // namespace math
}  // namespace anvil