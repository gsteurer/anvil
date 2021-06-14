#include "ads/list.h"
#include "gtest/gtest.h"

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

TEST(ListTests, Push) {
    List<int> test;
    test.PushFront(1);
    test.PushBack(2);
    test.PushFront(3);
    EXPECT_EQ(test[0], 3);
    EXPECT_EQ(test[1], 1);
    EXPECT_EQ(test[2], 2);
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