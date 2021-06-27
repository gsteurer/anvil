#pragma once
#include <time.h>

#include "anvil/types.h"
#include "time.h"

const timespec tzero = {0, 0};

long to_nsec(timespec t) {
    return (t.tv_sec * 1000000000) + t.tv_nsec;
}

struct TestResult {
    TestResult() {
        min = tzero;
        max = tzero;
        last = tzero;
        avg = tzero;
        total = tzero;
        count = 0;
    };
    timespec min;
    timespec max;
    timespec last;
    timespec avg;
    timespec total;
    isize_t count;
    void Update(timespec t) {
        last = t;

        if (min == tzero && max == tzero) {
            min = max = t;
        }

        if (t < min) {
            min = t;
        }
        if (t > max) {
            max = t;
        }
        total = total + t;
        count += 1;
        avg = total / count;
    }

    char* to_str(char* buf) {
        sprintf(buf, "last: %ldns || min: %ldns || max: %ldns || avg: %ldns || total: %ldns ", to_nsec(last), to_nsec(min), to_nsec(max), to_nsec(avg), to_nsec(total));
        return buf;
    }
};
