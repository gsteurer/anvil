#include "gtest/gtest.h"
#include "math/mat.h"
#include <cmath>

bool feq(float lhs, float rhs) {
    return std::fabs(lhs - rhs) < std::numeric_limits<float>::epsilon();
}

TEST(MatTest, Mat2x2f) {
    Mat2x2f m;
}

TEST(MatTest, Mat4x4f) {
    Mat4x4f m;
    EXPECT_TRUE(feq(m.get(0,0), 1.0));
}