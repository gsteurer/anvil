#pragma once
#include <string>

template <typename T>
struct Hashable {
    static long Hash(T key) {
        // https://stackoverflow.com/questions/1488186/stringifying-template-arguments
        // https://stackoverflow.com/questions/9004578/typeidt-name-alternative-in-c11
        static_assert(sizeof(T) != sizeof(T), "func must be specialized for this type!");
    }
};

template <>
struct Hashable<int> {
    static long Hash(int key) {
        return key;
    }
};
template <>
struct Hashable<long> {
    static long Hash(long key) {
        return key;
    }
};
template <>
struct Hashable<unsigned int> {
    static long Hash(long key) {
        return key;
    }
};
template <>
struct Hashable<unsigned long> {
    static long Hash(long key) {
        return key;
    }
};

// https://dave.cheney.net/2018/05/29/how-the-go-runtime-implements-maps-efficiently-without-generics
// https://en.wikipedia.org/wiki/MurmurHash
// https://stackoverflow.com/questions/19411742/what-is-the-default-hash-function-used-in-c-stdunordered-map
template <>
struct Hashable<std::string> {
    static long Hash(std::string key) {
        // @@@ FIXME
        return 55;
    }
};

template <>
struct Hashable<char*> {
    static long Hash(char* key) {
        // @@@ FIXME
        return 55;
    }
};