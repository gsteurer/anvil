#include "anvil/string/stlutils.h"

namespace anvil {
namespace string {
namespace stlutils {

std::vector<std::string> split(const std::string &s, std::string delim) {
    std::vector<std::string> result;
    std::string::size_type startpos = 0;

    std::size_t found = 0;
    while (found != std::string::npos) {
        found = s.find(delim, startpos);
        std::string item = s.substr(startpos, found - startpos);
        // if (item.compare("") != 0 && item.compare(delim) != 0) { // behaves like python split with this check
        result.push_back(item);
        // }
        startpos = found + delim.size();
    }

    return result;
}

std::string strip(const std::string &s) {
    std::string::size_type startpos = 0;

    for (std::string::size_type i = 0; i < s.size(); i++) {
        switch (s[i]) {
            case '\n':
            case '\t':
            case ' ':
            case '\r':
            case '\v':
            case '\f':
                startpos = i + 1;
                continue;
            default:
                break;
        };
        break;
    }

    std::string::size_type endsize = s.size() - startpos;
    for (std::string::size_type i = s.size() - 1; i >= 0 || i >= s.size(); i--) {
        switch (s[i]) {
            case '\n':
            case '\t':
            case ' ':
            case '\r':
            case '\v':
            case '\f':
                endsize -= 1;
                continue;
            default:
                break;
        };
        break;
    }

    return s.substr(startpos, endsize);
}

};  // namespace stlutils

};  // namespace string
};  // namespace anvil