#pragma once
namespace anvil {
typedef unsigned long int usize_t;
typedef long int isize_t;
typedef unsigned char byte_t;

typedef unsigned int u32_t;
typedef int i32_t;
typedef unsigned long u64_t;
typedef long i64_t;

typedef float f32_t;
typedef double f64_t;

template <typename T>
struct limit {
    static const T max;
    static const T min;
    static const T epsilon;
};

template <>
struct limit<u64_t> {
    static const u64_t max = 18446744073709551615U;
    static const u64_t min = 0U;
};

template <>
struct limit<i64_t> {
    static const i64_t max = 9223372036854775807L;
    static const i64_t min = -9223372036854775807L;
};

// @@@ TODO float

}  // namespace anvil
