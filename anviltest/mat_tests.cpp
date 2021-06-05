#include "gtest/gtest.h"
#include "math/mat.h"
#include "math/vec.h"
#include "math/util.h"

Mat4x4f NewTestMatrix() {
    Mat4x4f m;
    for(int idx = 0; idx < 16; idx ++) {
        m[idx] = static_cast<float>(1 + idx);
    }
    return m;
}

TEST(MatTest, Ctor) {
    auto m = NewTestMatrix();
    auto expected = NewTestMatrix();
    auto id = Identity();
    auto test = Identity();
    test = m; 
    EXPECT_EQ(test, expected);
    EXPECT_NE(test, id);
}

TEST(MatTest, Cmp) {
    auto m = Mat4x4f();
    m(0,0) = 1.0;
    m(1,1) = 1.0;
    m(2,2) = 1.0;
    m(3,3) = 1.0;
    auto id = Identity();
    EXPECT_TRUE(m == id);
}

TEST(MatTest, Assignment) {
    Mat4x4f m;
    for (int idx = 0; idx < 16; idx++) {
        EXPECT_TRUE(eq(m.e[idx], 0.0));
    }

    m(0,0) = 3.0;

    Mat4x4f i = Identity();
    EXPECT_TRUE(eq(i(0,0), 1.0));
}

TEST(MatTest, Str) {
    auto m = NewTestMatrix();
    const char* expected = "[\n\t1.0,5.0,9.0,13.0\n\t2.0,6.0,10.0,14.0\n\t3.0,7.0,11.0,15.0\n\t4.0,8.0,12.0,16.0\n]";
    EXPECT_EQ(std::string(expected), str(m,1));
}