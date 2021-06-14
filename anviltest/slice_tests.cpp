#include <cstdlib>
#include <string>

#include "ads/arrayutils.h"
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
    for (int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    for (int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }
}

TEST(SliceTests, Bracket) {
    Slice<int> test;
    int size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }
    EXPECT_EQ(test.Length(), size);
    EXPECT_LT(test.Length(), test.Capacity());
    for (int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }

    test[25] = 12345;
    EXPECT_EQ(test[25], 12345);
}

TEST(SliceTests, Scramble) {
    Slice<int> test;
    int size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    scramble(test, test.Length() - 1);

    for (int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test.IndexOf(idx + 1).result, Option<int>::Some);
    }
}

TEST(SliceTests, Quicksort) {
    Slice<int> test;
    Slice<int> expected;
    int size = 1000;
    EXPECT_EQ(test.Length(), 0);
    for (int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        expected.Insert(idx + 1);
    }

    scramble(test, test.Length() - 1);
    quicksort(test, 0, test.Length() - 1);

    for (int idx = 0; idx < size; idx++) {
        auto item = test.IndexOf(idx + 1);
        EXPECT_EQ(item.result, Option<int>::Some);
        EXPECT_EQ(item.value, idx);
        EXPECT_EQ(test[idx], expected[idx]);
    }
}

TEST(SliceTests, Heapsort) {
    Slice<int> test;
    Slice<int> expected;
    int size = 10;
    EXPECT_EQ(test.Length(), 0);
    for (int idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        expected.Insert(idx + 1);
    }

    scramble(test, test.Length() - 1);
    heapsort(test, test.Length() - 1);

    /*
    @@@ todo: 
    // check max heap property
    for (int idx = test.Length() - 1; idx > 0; idx--) {
        EXPECT_TRUE(test[idx / 2] >= test[idx]);
    }
    */

    for (int idx = 0; idx < size; idx++) {
        auto item = test.IndexOf(idx + 1);
        EXPECT_EQ(item.result, Option<int>::Some);
        EXPECT_EQ(item.value, idx);
        EXPECT_EQ(test[idx], expected[idx]);
    }
}