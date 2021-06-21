#include "ads/arrayutils.h"
#include "ads/list.h"
#include "gtest/gtest.h"
#include "option.h"

::testing::AssertionResult verifyList(List<int>& list, int* expected) {
    for (int idx = 0; idx < list.Length(); idx++) {
        if (list[idx] != expected[idx]) {
            return ::testing::AssertionFailure() << "expected " << expected[idx] << " at index " << idx << " got " << list[idx];
        }
    }
    return ::testing::AssertionSuccess();
}

TEST(ListTests, PushBack) {
    List<int> test;
    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        test.PushBack(idx + 1);
    }
    for (int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], idx + 1);
    }
}

TEST(ListTests, PushFront) {
    List<int> test;
    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        test.PushFront(idx + 1);
    }
    int value = size;
    for (int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], value);
        value--;
    }
}

TEST(ListTests, Bracket) {
    List<int> test;
    test.PushFront(3);
    test.PushFront(2);
    test.PushFront(1);
    EXPECT_EQ(test[0], 1);
    EXPECT_EQ(test[1], 2);
    EXPECT_EQ(test[2], 3);
    test[0] = 45;
    test[1] = 56;
    test[2] = 67;
    EXPECT_EQ(test[0], 45);
    EXPECT_EQ(test[1], 56);
    EXPECT_EQ(test[2], 67);
}

TEST(ListTests, Push) {
    List<int> test;
    test.PushFront(1);
    test.PushBack(2);
    test.PushFront(3);
    EXPECT_EQ(test[0], 3);
    EXPECT_EQ(test[1], 1);
    EXPECT_EQ(test[2], 2);
}

TEST(ListTests, IndexOf) {
    List<int> test;
    test.PushFront(3);
    test.PushFront(3);
    test.PushFront(3);
    test.PushFront(1);
    EXPECT_EQ(test.Length(), 4);
    Option<int> result = test.IndexOf(3);
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 1);
}

TEST(ListTests, InsertAt) {
    List<int> test;

    test.InsertAt(1, 0);
    EXPECT_EQ(test[0], 1);

    test.InsertAt(2, 0);
    EXPECT_EQ(test[0], 2);
    EXPECT_EQ(test[1], 1);

    test.InsertAt(3, 0);
    EXPECT_EQ(test[0], 3);
    EXPECT_EQ(test[1], 2);
    EXPECT_EQ(test[2], 1);

    test.InsertAt(4, 1);  // insert before 2, [3,4,2,1]
    int expected4[4] = {3, 4, 2, 1};
    EXPECT_TRUE(verifyList(test, expected4));

    test.InsertAt(5, 3);  // insert before 3, [3,4,2,5,1]
    int expected5[5] = {3, 4, 2, 5, 1};
    EXPECT_TRUE(verifyList(test, expected5));

    test.InsertAt(6, 5);  // insert after 1, [3,4,2,5,1,6]
    int expected6[6] = {3, 4, 2, 5, 1, 6};
    EXPECT_TRUE(verifyList(test, expected6));

    test.InsertAt(7, 0);
    int expected7[7] = {7, 3, 4, 2, 5, 1, 6};
    EXPECT_TRUE(verifyList(test, expected7));

    test.InsertAt(8, 99);
    int expected8[8] = {7, 3, 4, 2, 5, 1, 6, 8};
    EXPECT_TRUE(verifyList(test, expected8));

    EXPECT_EQ(test.Length(), 8);
}

TEST(ListTests, PopFront) {
    List<int> test;
    test.PushFront(1);
    Option<int> result = test.PopFront();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 1);
    EXPECT_EQ(test.Length(), 0);

    test.PushFront(1);
    test.PushFront(2);
    test.PushBack(3);
    test.InsertAt(4, 1);
    EXPECT_EQ(test.Length(), 4);
    // test = [2, 4, 1, 3]
    result = test.PopFront();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 2);
    // test = [4, 1, 3]

    result = test.PopFront();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 4);
    // test = [1, 3]

    result = test.PopFront();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 1);
    // test = [3]

    result = test.PopFront();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 3);
    // test = []

    result = test.PopFront();
    EXPECT_EQ(result.result, Option<int>::None);
    EXPECT_EQ(test.Length(), 0);
}

TEST(ListTests, PopBack) {
    List<int> test;
    test.PushBack(1);
    Option<int> result = test.PopBack();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 1);
    EXPECT_EQ(test.Length(), 0);

    test.PushBack(1);
    test.PushBack(2);
    test.PushBack(3);
    test.InsertAt(4, 1);
    EXPECT_EQ(test.Length(), 4);
    // test = [1, 4, 2, 3]
    result = test.PopBack();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 3);
    // test = [1, 4, 2]

    result = test.PopBack();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 2);
    // test = [1, 4]

    result = test.PopBack();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 4);
    // test = [1]

    result = test.PopBack();
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 1);
    // test = []

    result = test.PopBack();
    EXPECT_EQ(result.result, Option<int>::None);
    EXPECT_EQ(test.Length(), 0);
}

TEST(ListTests, ScrambleAndSort) {
    List<int> test;
    List<int> expected;
    int size = 100;
    for (int idx = 0; idx < size; idx++) {
        test.PushFront(idx + 1);
        expected.PushBack(idx + 1);
    }

    scramble(test, test.Length() - 1);
    quicksort(test, 0, test.Length() - 1);

    for (int idx = 0; idx < size; idx++) {
        EXPECT_EQ(test[idx], expected[idx]);
    }
}

TEST(ListTests, RemoveAt) {
    List<int> test;
    test.PushBack(1);
    test.PushBack(3);
    test.PushBack(5);
    test.PushBack(9);
    for (int idx = 0; idx < 4; idx++) {
        Option<int> result = test.RemoveAt(0);
        int expected[4] = {1, 3, 5, 9};
        EXPECT_EQ(result.result, Option<int>::Some);
        EXPECT_EQ(result.value, expected[idx]);
    }
    EXPECT_EQ(test.Length(), 0);

    test.PushBack(1);
    test.PushBack(3);
    test.PushBack(5);
    test.PushBack(9);
    for (int idx = 0; idx < 4; idx++) {
        Option<int> result = test.RemoveAt(test.Length() - 1);
        int expected[4] = {9, 5, 3, 1};
        EXPECT_EQ(result.result, Option<int>::Some);
        EXPECT_EQ(result.value, expected[idx]);
    }
    EXPECT_EQ(test.Length(), 0);

    test.PushBack(1);
    test.PushBack(3);
    test.PushBack(5);
    Option<int> result = test.RemoveAt(1);
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 3);
    test.PushFront(9);
    test.PushBack(11);
    //9, 1, 5, 11
    result = test.RemoveAt(2);
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 5);
    EXPECT_EQ(test.Length(), 3);
    EXPECT_EQ(test[0], 9);
    EXPECT_EQ(test[1], 1);
    EXPECT_EQ(test[2], 11);

    result = test.Remove(9);
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 9);
}
