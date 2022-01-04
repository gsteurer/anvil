#pragma once

#include <array>

#include "anvil/containers/slice.h"
#include "anvil/math/vec4f.h"
#include "anvil/types.h"
namespace anvil {
namespace file {

struct Mesh {
    anvil::containers::Slice<anvil::math::Vec4f> verts;
    anvil::containers::Slice<std::array<uint32_t, 3>> faces;
};

};  // namespace file
};  // namespace anvil
