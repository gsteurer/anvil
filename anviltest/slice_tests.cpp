#include <cstdlib>
#include <string>

#include "ads/arrayutils.h"
#include "ads/slice.h"
#include "foo.h"
#include "gtest/gtest.h"
#include "option.h"

TEST(SliceTests, Ctor) {
    anvil::Slice<anvil::isize_t> test;
    EXPECT_EQ(test.Length(), 0);
    EXPECT_GT(test.Capacity(), 0);
}

TEST(SliceTests, InsertPrimitive) {
    anvil::Slice<anvil::isize_t> test;
    anvil::isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    for (anvil::isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }
}

TEST(SliceTests, InsertCompound) {
    anvil::Slice<Foo<anvil::isize_t>> test;
    anvil::isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        Foo<anvil::isize_t> foo(idx + 1);
        test.Insert(foo);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    for (anvil::isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }
}

TEST(SliceTests, Bracket) {
    anvil::Slice<anvil::isize_t> test;
    anvil::isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }
    EXPECT_EQ(test.Length(), size);
    EXPECT_LT(test.Length(), test.Capacity());
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }

    test[25] = 12345;
    EXPECT_EQ(test[25], 12345);
}

TEST(SliceTests, Scramble) {
    anvil::Slice<anvil::isize_t> test;
    anvil::isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    anvil::scramble(test, test.Length() - 1);

    for (anvil::isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test.IndexOf(idx + 1).result, Option<anvil::isize_t>::Some);
    }
}

TEST(SliceTests, Quicksort) {
    anvil::Slice<anvil::isize_t> test;
    anvil::Slice<anvil::isize_t> expected;
    anvil::isize_t size = 1000;
    EXPECT_EQ(test.Length(), 0);
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        expected.Insert(idx + 1);
    }

    anvil::scramble(test, test.Length() - 1);
    anvil::quicksort(test, 0, test.Length() - 1);

    for (anvil::isize_t idx = 0; idx < size; idx++) {
        auto item = test.IndexOf(idx + 1);
        EXPECT_EQ(item.result, Option<anvil::isize_t>::Some);
        EXPECT_EQ(item.value, idx);
        EXPECT_EQ(test[idx], expected[idx]);
    }
}

TEST(SliceTests, Heapsort) {
    anvil::Slice<anvil::isize_t> test;
    anvil::Slice<anvil::isize_t> expected;
    anvil::isize_t size = 10;
    EXPECT_EQ(test.Length(), 0);
    for (anvil::isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        expected.Insert(idx + 1);
    }

    anvil::scramble(test, test.Length() - 1);
    anvil::heapsort(test, test.Length() - 1);

    /*
    @@@ todo: 
    // check max heap property
    for (anvil::isize_t idx = test.Length() - 1; idx > 0; idx--) {
        EXPECT_TRUE(test[idx / 2] >= test[idx]);
    }
    */

    for (anvil::isize_t idx = 0; idx < size; idx++) {
        auto item = test.IndexOf(idx + 1);
        EXPECT_EQ(item.result, Option<anvil::isize_t>::Some);
        EXPECT_EQ(item.value, idx);
        EXPECT_EQ(test[idx], expected[idx]);
    }
}