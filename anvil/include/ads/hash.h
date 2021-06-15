#pragma once

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
        // @@@ FIXME
        return 55;
    }
};