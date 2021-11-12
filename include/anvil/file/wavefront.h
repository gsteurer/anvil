#pragma once

#include <string>

#include "anvil/file/mesh.h"

namespace anvil {
namespace file {
namespace wavefront {

Mesh parse(std::string filename);

};  // namespace wavefront
};  // namespace file
};  // namespace anvil
