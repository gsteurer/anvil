#include <cstdlib>
#include <string>

#include "ads/slice.h"
#include "gtest/gtest.h"
#include "option.h"

TEST(SliceTests, Ctor) {
    Slice<int> test;
    EXPECT_EQ(test.Length(), 0);
    EXPECT_GT(test.Capacity(), 0);
}

TEST(SliceTests, InsertPrimitive) {
    Slice<int> test;
    int size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (unsigned int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    for (unsigned int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }
}

TEST(SliceTests, Bracket) {
    Slice<int> test;
    int size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (unsigned int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }
    EXPECT_EQ(test.Length(), size);
    EXPECT_LT(test.Length(), test.Capacity());
    for (unsigned int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }

    test[25] = 12345;
    EXPECT_EQ(test[25], 12345);
}

TEST(SliceTests, Scramble) {
    Slice<int> test;
    int size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (unsigned int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    scramble(test, test.Length());

    for (unsigned int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test.IndexOf(idx + 1).result, Option<unsigned int>::Some);
    }
}
