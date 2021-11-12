#pragma once
#include <string>
#include <vector>

namespace anvil {
namespace file {

struct Mesh {
    std::vector<double> verts;
    std::vector<double> faces;
};

};  // namespace file
};  // namespace anvil
