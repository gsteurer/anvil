#pragma once
#include <time.h>

#include "types.h"

inline bool operator==(const timespec& lhs, const timespec& rhs) {
    return lhs.tv_nsec == rhs.tv_nsec && lhs.tv_sec == rhs.tv_sec;
}

inline bool operator<(const timespec& lhs, const timespec& rhs) {
    long lnsec = lhs.tv_sec > 0 ? lhs.tv_sec + 1000000000 + lhs.tv_nsec : lhs.tv_nsec;
    long rnsec = rhs.tv_sec > 0 ? rhs.tv_sec + 1000000000 + rhs.tv_nsec : rhs.tv_nsec;

    return lnsec < rnsec;
}

inline bool operator>(const timespec& lhs, const timespec& rhs) {
    long lnsec = lhs.tv_sec > 0 ? lhs.tv_sec + 1000000000 + lhs.tv_nsec : lhs.tv_nsec;
    long rnsec = rhs.tv_sec > 0 ? rhs.tv_sec + 1000000000 + rhs.tv_nsec : rhs.tv_nsec;

    return lnsec > rnsec;
}

// https://stackoverflow.com/questions/17705786/getting-negative-values-using-clock-gettime
inline timespec operator-(const timespec& lhs, const timespec& rhs) {
    timespec result;
    if (lhs.tv_nsec - rhs.tv_nsec < 0) {
        result.tv_nsec = lhs.tv_nsec - rhs.tv_nsec + 1000000000;
        result.tv_sec = lhs.tv_sec + rhs.tv_sec - 1;
    } else {
        result.tv_nsec = lhs.tv_nsec - rhs.tv_nsec;
        result.tv_sec = lhs.tv_sec - rhs.tv_sec;
    }
    return result;
}

inline timespec operator+(const timespec& lhs, const timespec& rhs) {
    timespec result;
    if (lhs.tv_nsec + rhs.tv_nsec >= 1000000000) {
        result.tv_nsec = lhs.tv_nsec + rhs.tv_nsec - 1000000000;
        result.tv_sec = lhs.tv_sec + rhs.tv_sec + 1;
    } else {
        result.tv_nsec = lhs.tv_nsec + rhs.tv_nsec;
        result.tv_sec = lhs.tv_sec + rhs.tv_sec;
    }
    return result;
}

inline timespec operator/(const timespec& t, isize_t n) {
    timespec result;

    long nsec = t.tv_sec > 0 ? t.tv_sec + 1000000000 + t.tv_nsec / n : t.tv_nsec / n;

    result.tv_sec = nsec / 1000000000;
    result.tv_nsec = nsec - (result.tv_sec * 1000000000);

    return result;
}