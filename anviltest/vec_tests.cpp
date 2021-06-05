#include "gtest/gtest.h"
#include "math/vec.h"
#include <cmath>

TEST(EqTest, FloatEquality) {
    EXPECT_TRUE(eq(0.0, 0.0));
    EXPECT_TRUE(eq(-0.0, -0.0));
    EXPECT_TRUE(eq(-0.0, 0.0));
    EXPECT_TRUE(eq(0.0, -0.0));
    EXPECT_FALSE(eq(0.0, 0.1));
    EXPECT_FALSE(eq(0.1, 0.0));
    EXPECT_TRUE(eq(0.0000000001, 0.0000000001));
}

TEST(Vec4fTest, Ctor) {
    Vec4f v(4.0, 3.0, 2.0, 1.0);
    EXPECT_EQ(v.x, 4.0);    
    EXPECT_EQ(v.y, 3.0);    
    EXPECT_EQ(v.z, 2.0);    
    EXPECT_EQ(v.w, 1.0);    
    EXPECT_TRUE(point(v));
    EXPECT_FALSE(vector(v));
}

TEST(Vec4fTest, Vec4f) {
    Vec4f a(1.0, 2.0, 3.0, 4.0);
    Vec4f b(4.0, 3.0, 2.0, 1.0);
    Vec4f c(5.0, 5.0, 5.0, 5.0);
    EXPECT_TRUE((a + b) == c);    
}

TEST(Vec4fTest, Mag) {
    Vec4f v1(1.0, 2.0, 3.0, 0.0);
    Vec4f v2(-1.0, -2.0, -3.0, -0.0);
    float expected = std::sqrt(14); 
    EXPECT_TRUE(eq(mag(v1), expected));
    EXPECT_TRUE(eq(mag(v1), mag(v2)));
}

TEST(Vec4fTest, Norm) {
    Vec4f v(1.0, 2.0, 3.0, 0.0);
    Vec4f n = norm(v);
    float test = mag(n);
    EXPECT_TRUE(eq(test, 1.0));
    EXPECT_TRUE(eq(n.x, 1.0/std::sqrt(14)));
    EXPECT_TRUE(eq(n.y, 2.0/std::sqrt(14)));
    EXPECT_TRUE(eq(n.z, 3.0/std::sqrt(14)));
    EXPECT_TRUE(eq(n.w, 0.0));
}

TEST(Vec4fTest, Dot) {
    Vec4f v1(1.0, 2.0, 3.0, 0.0);
    Vec4f v2(2.0, 3.0, 4.0, 0.0);
    float d = dot(v1, v2);
    EXPECT_TRUE(eq(d, 20.0));
}

TEST(Vec4fTest, Cross) {
    Vec4f v1(1.0, 2.0, 3.0, 0.0);
    Vec4f v2(2.0, 3.0, 4.0, 0.0);
    Vec4f expected = cross(v1, v2);
    EXPECT_TRUE(eq(expected.x, -1.0));
    EXPECT_TRUE(eq(expected.y, 2.0));
    EXPECT_TRUE(eq(expected.z, -1.0));
    expected = cross(v2, v1);
    EXPECT_TRUE(eq(expected.x, 1.0));
    EXPECT_TRUE(eq(expected.y, -2.0));
    EXPECT_TRUE(eq(expected.z, 1.0));
}