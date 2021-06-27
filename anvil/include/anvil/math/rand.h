#pragma once
// https://en.wikipedia.org/wiki/Linear_congruential_generator
// http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf // page 256
// https://stackoverflow.com/questions/6161322/using-stdlibs-rand-from-multiple-threads // thread safety

#include "anvil/types.h"

namespace anvil {
namespace math {

static u64_t next = 1;

inline u64_t rand(void) {
    next = next * 1103515245 + 12345;
    return (u64_t)(next / 65536) % 32768;
}

inline void srand(u64_t seed) {
    next = seed;
}

}  // namespace math
}  // namespace anvil
