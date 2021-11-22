#include "anvil/containers/priorityqueue.h"
#include "anvil/option.h"
#include "anvil/types.h"
#include "gtest/gtest.h"

using namespace anvil::containers;

TEST(PriorityQueueTests, MaxPushPopPeek) {
    PriorityQueue<MaxPriorityQueue, u64_t> test;
    test.Push(5);
    test.Push(4);
    test.Push(3);
    test.Push(11);
    test.Push(8);
    test.Push(15);

    // peek
    Option<u64_t> result = test.Peek();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(15U, result.value);

    // pop
    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(15U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(11U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(8U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(5U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(4U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(3U, result.value);
}

TEST(PriorityQueueTests, MinPushPopPeek) {
    PriorityQueue<MinPriorityQueue, u64_t> test;
    test.Push(5);
    test.Push(4);
    test.Push(3);
    test.Push(11);
    test.Push(8);
    test.Push(15);

    // peek
    Option<u64_t> result = test.Peek();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(3U, result.value);

    // pop
    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(3U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(4U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(5U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(8U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(11U, result.value);

    result = test.Pop();
    EXPECT_EQ(Option<u64_t>::Some, result.result);
    EXPECT_EQ(15U, result.value);
}