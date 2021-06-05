#include "gtest/gtest.h"
#include "math/mat.h"
#include "math/vec.h"
#include "math/util.h"

TEST(MatTest, Mat2x2f) {
    Mat2x2f m;
}

TEST(MatTest, Mat4x4f) {
    Mat4x4f m;
    EXPECT_TRUE(eq(m.get(0,0), 1.0));
}