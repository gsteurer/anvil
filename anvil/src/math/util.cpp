#include "math/util.h"
#include <limits>

bool eq(float lhs, float rhs) {
    return std::fabs(lhs - rhs) < std::numeric_limits<float>::epsilon();
}
