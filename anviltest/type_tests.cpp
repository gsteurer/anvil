#include "gtest/gtest.h"
#include "types.h"

TEST(TypeTests, Types) {
    EXPECT_EQ(sizeof(anvil::usize_t), 8);
    EXPECT_EQ(sizeof(anvil::isize_t), 8);
    EXPECT_EQ(sizeof(anvil::byte_t), 1);
    EXPECT_EQ(sizeof(anvil::f64_t), 8);
    EXPECT_EQ(sizeof(anvil::f32_t), 4);
    EXPECT_EQ(sizeof(anvil::i64_t), 8);
    EXPECT_EQ(sizeof(anvil::i32_t), 4);
    EXPECT_EQ(sizeof(anvil::u64_t), 8);
    EXPECT_EQ(sizeof(anvil::u32_t), 4);
}