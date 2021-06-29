#pragma once
#include <time.h>

#include "anvil/time.h"
#include "testresult.h"

static const clockid_t PRECISION = CLOCK_THREAD_CPUTIME_ID;

class TestCase {
   public:
    virtual void Setup() = 0;
    virtual void Execute() = 0;
    virtual void TearDown() = 0;
    TestResult Run() {
        this->Setup();
        timespec t_initial, t_final, delta;
        clock_gettime(PRECISION, &t_initial);
        this->Execute();
        clock_gettime(PRECISION, &t_final);
        delta = t_final - t_initial;
        this->TearDown();
        result.Update(delta);
        return result;
    }
    TestResult result;
};