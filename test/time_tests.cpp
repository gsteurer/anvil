#include <time.h>

#include "anvil/time.h"
#include "gtest/gtest.h"

TEST(TimeTests, Ops) {
    timespec a, b, expected, result;
    a.tv_nsec = 1000;
    a.tv_sec = 1000;
    b.tv_nsec = 1000;
    b.tv_sec = 1000;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a < b);

    a.tv_nsec = 1;
    a.tv_sec = 1;
    b.tv_nsec = 2;
    b.tv_sec = 1;
    EXPECT_LT(a, b);
    EXPECT_GT(b, a);

    a.tv_nsec = 1;
    a.tv_sec = 1;
    b.tv_nsec = 1;
    b.tv_sec = 1;
    expected.tv_nsec = 0;
    expected.tv_sec = 0;
    EXPECT_EQ(expected, a - b);

    a.tv_nsec = 1000;
    a.tv_sec = 1000;
    b.tv_nsec = 1000;
    b.tv_sec = 1000;
    expected.tv_nsec = 2000;
    expected.tv_sec = 2000;
    EXPECT_EQ(expected, a + b);

    a.tv_nsec = 600000000;
    a.tv_sec = 1;
    b.tv_nsec = 500000000;
    b.tv_sec = 1;
    expected.tv_nsec = 100000000;
    expected.tv_sec = 3;
    result = a + b;
    EXPECT_EQ(expected.tv_sec, result.tv_sec);
    EXPECT_EQ(expected.tv_nsec, result.tv_nsec);

    a.tv_nsec = 0;
    a.tv_sec = 1;
    b.tv_nsec = 1;
    b.tv_sec = 0;
    expected.tv_nsec = 999999999;
    expected.tv_sec = 0;
    result = a - b;
    EXPECT_EQ(expected.tv_sec, result.tv_sec);
    EXPECT_EQ(expected.tv_nsec, result.tv_nsec);

    a.tv_nsec = 0;
    a.tv_sec = 1;
    b.tv_nsec = 100;
    b.tv_sec = 0;
    expected.tv_nsec = 999999900;
    expected.tv_sec = 0;
    result = a - b;
    EXPECT_EQ(expected.tv_sec, result.tv_sec);
    EXPECT_EQ(expected.tv_nsec, result.tv_nsec);
}