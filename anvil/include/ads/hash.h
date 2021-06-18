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

// hash a struct:
// https://stackoverflow.com/questions/19195183/how-to-properly-hash-the-custom-struct
// https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine

// https://en.wikipedia.org/wiki/Hash_function#Multiplicative_hashing
// https://en.wikipedia.org/wiki/Universal_hashing#Avoiding_modular_arithmetic
// https://stackoverflow.com/questions/11871245/knuth-multiplicative-hash
// https://algs4.cs.princeton.edu/34hash/
// https://gist.github.com/badboy/6267743
// http://www.burtleburtle.net/bob/hash/doobs.html
// https://classes.engineering.wustl.edu/cse241/handouts/hash-functions.pdf
template <>
struct Hashable<int> {
    static long Hash(int key) {
        unsigned long temp = key >> (sizeof(int) * 8 - 1);
        key ^= temp;
        key += temp & 1;
        unsigned long hash = key;
        unsigned int phi = 2654435769;  // pow(2,32) * (-1 + math.sqrt(5)) / 2 // golden ratio

        return (hash * phi) >> 32;
    }
};

// http://zimbry.blogspot.com/2011/09/better-bit-mixing-improving-on.html
// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
// https://www.usna.edu/Users/cs/crabbe/IC312/current/units/06/unit.html
template <>
struct Hashable<long> {
    static long Hash(long key) {
        // unsigned long phi = 11400714819323199488L;  // pow(2,64) * (-1 + math.sqrt(5)) / 2 // golden ratio
        // return (key * phi) >> 64;
        unsigned long temp = key >> (sizeof(long) * 8 - 1);
        key ^= temp;
        key += temp & 1;
        unsigned long hash = key;
        hash ^= (hash >> 33);
        hash *= 0xff51afd7ed558ccd;
        hash ^= (hash >> 33);
        hash *= 0xc4ceb9fe1a85ec53;
        hash ^= (hash >> 33);
        return hash;
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

// https://stackoverflow.com/questions/1579721/why-are-5381-and-33-so-important-in-the-djb2-algorithm
inline unsigned long djb2(unsigned char* str) {
    unsigned long hash = 5381;
    int c;
    // http://www.cse.yorku.ca/~oz/hash.html
    while ((c = *str++)) {               // exits when c is zero, which is the null terminator \0
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

template <>
struct Hashable<std::string> {
    static long Hash(std::string key) {
        return djb2(reinterpret_cast<unsigned char*>(const_cast<char*>(key.c_str())));
    }
};

template <>
struct Hashable<unsigned char*> {
    static long Hash(unsigned char* key) {
        return djb2(key);
    }
};

template <>
struct Hashable<char*> {
    static long Hash(char* key) {
        return djb2(reinterpret_cast<unsigned char*>(key));
    }
};