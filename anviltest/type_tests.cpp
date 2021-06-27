#include "anvil/types.h"
#include "gtest/gtest.h"

TEST(TypeTests, Types) {
    EXPECT_EQ(sizeof(usize_t), 8U);
    EXPECT_EQ(sizeof(isize_t), 8U);
    EXPECT_EQ(sizeof(byte_t), 1U);
    EXPECT_EQ(sizeof(f64_t), 8U);
    EXPECT_EQ(sizeof(f32_t), 4U);
    EXPECT_EQ(sizeof(i64_t), 8U);
    EXPECT_EQ(sizeof(i32_t), 4U);
    EXPECT_EQ(sizeof(u64_t), 8U);
    EXPECT_EQ(sizeof(u32_t), 4U);
}