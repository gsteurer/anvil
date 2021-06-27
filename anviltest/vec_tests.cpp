#include <limits>

#include "anvil/math/util.h"
#include "anvil/math/vec4f.h"
#include "gtest/gtest.h"

using namespace anvil::math;

TEST(EqTest, FloatEquality) {
    EXPECT_TRUE(floateq(0.0f, 0.0f));
    EXPECT_TRUE(floateq(-0.0f, -0.0f));
    EXPECT_TRUE(floateq(-0.0f, 0.0f));
    EXPECT_TRUE(floateq(0.0f, -0.0f));
    EXPECT_FALSE(floateq(0.0f, 0.1f));
    EXPECT_FALSE(floateq(0.1f, 0.0f));
    EXPECT_TRUE(floateq(0.0000000001f, 0.0000000001f));
    EXPECT_TRUE(floateq(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()));
}

TEST(Vec4fTest, Ctor) {
    Vec4f v(4.0, 3.0, 2.0, 1.0);
    EXPECT_FLOAT_EQ(v.x, 4.0);
    EXPECT_FLOAT_EQ(v.y, 3.0);
    EXPECT_FLOAT_EQ(v.z, 2.0);
    EXPECT_FLOAT_EQ(v.w, 1.0);
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
    float expected = static_cast<float>(std::sqrt(14));
    EXPECT_FLOAT_EQ(mag(v1), expected);
    EXPECT_FLOAT_EQ(mag(v1), mag(v2));
}

TEST(Vec4fTest, Norm) {
    Vec4f v(1.0, 2.0, 3.0, 0.0);
    Vec4f n = norm(v);
    float test = mag(n);
    EXPECT_FLOAT_EQ(test, 1.0);
    EXPECT_FLOAT_EQ(n.x, 1.0f / static_cast<float>(std::sqrt(14)));
    EXPECT_FLOAT_EQ(n.y, 2.0f / static_cast<float>(std::sqrt(14)));
    EXPECT_FLOAT_EQ(n.z, 3.0f / static_cast<float>(std::sqrt(14)));
    EXPECT_FLOAT_EQ(n.w, 0.0);
}

TEST(Vec4fTest, Dot) {
    Vec4f v1(1.0, 2.0, 3.0, 0.0);
    Vec4f v2(2.0, 3.0, 4.0, 0.0);
    float d = dot(v1, v2);
    EXPECT_FLOAT_EQ(d, 20.0);
    EXPECT_FLOAT_EQ(dot(Vec4f(1.0, 2.0, 3.0, 4.0), Vec4f(1.0, 2.0, 3.0, 1.0)), 18.0);
}

TEST(Vec4fTest, Cross) {
    Vec4f v1(1.0, 2.0, 3.0, 0.0);
    Vec4f v2(2.0, 3.0, 4.0, 0.0);
    Vec4f expected = cross(v1, v2);
    EXPECT_FLOAT_EQ(expected.x, -1.0);
    EXPECT_FLOAT_EQ(expected.y, 2.0);
    EXPECT_FLOAT_EQ(expected.z, -1.0);
    expected = cross(v2, v1);
    EXPECT_FLOAT_EQ(expected.x, 1.0);
    EXPECT_FLOAT_EQ(expected.y, -2.0);
    EXPECT_FLOAT_EQ(expected.z, 1.0);
}

TEST(Vec4fTest, Str) {
    Vec4f v1(1.0, 2.0, 3.0, 0.0);
    EXPECT_EQ(std::string("(1.0, 2.0, 3.0, 0.0)"), str(v1, 1));
}