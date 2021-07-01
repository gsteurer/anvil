#include <cstdlib>
#include <string>

#include "anvil/containers/arrayutils.h"
#include "anvil/containers/slice.h"
#include "anvil/math/rand.h"
#include "anvil/option.h"
#include "foo.h"
#include "gtest/gtest.h"

using namespace anvil::containers;

TEST(SliceTests, Ctor) {
    Slice<isize_t> test;
    EXPECT_EQ(test.Length(), 0);
    EXPECT_GT(test.Capacity(), 0);
}

TEST(SliceTests, InsertPrimitive) {
    Slice<isize_t> test;
    isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    for (isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }
}

TEST(SliceTests, InsertCompound) {
    Slice<Foo<isize_t>> test;
    isize_t size = 100;
    EXPECT_EQ(test.Length(), 0L);
    for (isize_t idx = 0; idx < size; idx++) {
        Foo<isize_t> foo(static_cast<int>(idx + 1));
        test.Insert(foo);
        EXPECT_EQ(test.Length(), idx + 1L);
    }

    for (isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], static_cast<int>(idx + 1L));
    }
}

TEST(SliceTests, Bracket) {
    Slice<isize_t> test;
    isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }
    EXPECT_EQ(test.Length(), size);
    EXPECT_LT(test.Length(), test.Capacity());
    for (isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }

    test[25] = 12345;
    EXPECT_EQ(test[25], 12345);
}

TEST(SliceTests, Scramble) {
    Slice<isize_t> test;
    isize_t size = 100;
    EXPECT_EQ(test.Length(), 0);
    for (isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        EXPECT_EQ(test.Length(), idx + 1);
    }

    scramble(test, test.Length() - 1);

    for (isize_t idx = 0; idx < size; idx++) {
        EXPECT_EQ(test.IndexOf(idx + 1).result, Option<isize_t>::Some);
    }
}

TEST(SliceTests, Quicksort) {
    Slice<isize_t> test;
    Slice<isize_t> expected;
    isize_t size = 1000;
    EXPECT_EQ(test.Length(), 0);
    for (isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        expected.Insert(idx + 1);
    }

    scramble(test, test.Length() - 1);
    quicksort(test, 0, test.Length() - 1);

    for (isize_t idx = 0; idx < size; idx++) {
        auto item = test.IndexOf(idx + 1);
        EXPECT_EQ(item.result, Option<isize_t>::Some);
        EXPECT_EQ(item.value, idx);
        EXPECT_EQ(test[idx], expected[idx]);
    }
}

TEST(SliceTests, Heapsort) {
    Slice<isize_t> test;
    Slice<isize_t> expected;
    isize_t size = 10;
    EXPECT_EQ(test.Length(), 0);
    for (isize_t idx = 0; idx < size; idx++) {
        test.Insert(idx + 1);
        expected.Insert(idx + 1);
    }

    scramble(test, test.Length() - 1);
    heapsort(test, test.Length() - 1);

    /*
    @@@ todo: 
    // check max heap property
    for (isize_t idx = test.Length() - 1; idx > 0; idx--) {
        EXPECT_TRUE(test[idx / 2] >= test[idx]);
    }
    */

    for (isize_t idx = 0; idx < size; idx++) {
        auto item = test.IndexOf(idx + 1);
        EXPECT_EQ(item.result, Option<isize_t>::Some);
        EXPECT_EQ(item.value, idx);
        EXPECT_EQ(test[idx], expected[idx]);
    }
}

TEST(SliceTests, RemoveSimple) {
    Slice<isize_t> test;
    test.Insert(5);
    EXPECT_EQ(test.Remove(0), 5);
    EXPECT_EQ(test.Length(), 0);

    test.Insert(5);
    test.Insert(9);
    test.Insert(12);
    EXPECT_EQ(12, test.Remove(2));
    EXPECT_EQ(test.Length(), 2);
}

TEST(SliceTests, Remove) {
    isize_t size = 100;

    Slice<i64_t> test;
    i64_t* elements = new isize_t[size];

    for (isize_t idx = 0; idx < size; idx++) {
        i64_t val = static_cast<i64_t>(anvil::math::rand());
        test.Insert(val);
        elements[idx] = val;
    }

    scramble(elements, test.Length() - 1);

    for (isize_t idx = 0; idx < size; idx++) {
        Option<isize_t> jdx = test.IndexOf(elements[idx]);
        EXPECT_EQ(Option<isize_t>::Some, jdx.result);
        EXPECT_EQ(elements[idx], test.Remove(jdx.value));
        EXPECT_EQ(test.Length(), size - idx - 1);
    }

    delete[] elements;
}

TEST(SliceTests, GetSlice) {
    isize_t size = 10;

    Slice<i64_t> test;

    for (isize_t idx = 0; idx < size; idx++) {
        test.Insert(anvil::math::rand());
    }
    Slice<i64_t> s = test.GetSlice(5, 8);
    EXPECT_EQ(3, s.Length());
    EXPECT_EQ(s[0], test[5]);
    EXPECT_EQ(s[1], test[6]);
    EXPECT_EQ(s[2], test[7]);
}