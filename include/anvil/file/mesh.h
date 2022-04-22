#pragma once

#include <array>

#include "anvil/containers/slice.h"
#include "anvil/math/vec4f.h"
#include "anvil/types.h"
namespace anvil {
namespace file {

struct Face {
    uint32_t vertex;
    uint32_t texture;
    uint32_t normal;
};

struct Mesh {
    anvil::containers::Slice<anvil::math::Vec4f> verts;
    anvil::containers::Slice<anvil::math::Vec4f> textures;
    anvil::containers::Slice<anvil::math::Vec4f> normals;
    anvil::containers::Slice<std::array<Face, 3>> faces;
};

};  // namespace file
};  // namespace anvil
