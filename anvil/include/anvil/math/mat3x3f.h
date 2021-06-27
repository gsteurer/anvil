#pragma once

#include "anvil/types.h"

namespace anvil {
namespace math {

struct Mat3x3f {
    f64_t m_elements[9];
    Mat3x3f();
};

}  // namespace math
}  // namespace anvil
