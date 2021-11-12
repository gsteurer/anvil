#pragma once

#include <string>
#include <vector>

namespace anvil {
namespace string {
namespace stlutils {

std::vector<std::string> split(const std::string &s, std::string delim);

std::string strip(const std::string &s);

};  // namespace stlutils
};  // namespace string
};  // namespace anvil
