#include "gtest/gtest.h"
#include "math/mat.h"
#include "math/mat4x4f.h"
#include "math/util.h"
#include "math/vec4f.h"

Mat4x4f NewTestMatrix() {
    Mat4x4f m;
    for (int idx = 0; idx < 16; idx++) {
        m[idx] = static_cast<float>(1 + idx);
    }
    return m;
}

TEST(Mat4x4fTest, Ctor) {
    auto m = NewTestMatrix();
    auto expected = NewTestMatrix();
    auto id = Identity();
    auto test = Identity();
    test = m;
    EXPECT_EQ(test, expected);
    EXPECT_NE(test, id);
}

TEST(Mat4x4fTest, Cmp) {
    auto m = Mat4x4f();
    m(0, 0) = 1.0;
    m(1, 1) = 1.0;
    m(2, 2) = 1.0;
    m(3, 3) = 1.0;
    auto id = Identity();
    EXPECT_EQ(m, id);
    float data[16] = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0};
    auto m2 = Mat4x4f(data);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            EXPECT_FLOAT_EQ(m2(row, col), data[row * 4 + col]);
        }
    }
}

TEST(Mat4x4fTest, Assignment) {
    Mat4x4f m;
    for (int idx = 0; idx < 16; idx++) {
        EXPECT_FLOAT_EQ(m.m_elements[idx], 0.0);
    }

    m(0, 0) = 3.0;

    Mat4x4f i = Identity();
    EXPECT_FLOAT_EQ(i(0, 0), 1.0);
}

TEST(Mat4x4fTest, Str) {
    auto m = NewTestMatrix();
    const char* expected = "[\n\t1.0,2.0,3.0,4.0\n\t5.0,6.0,7.0,8.0\n\t9.0,10.0,11.0,12.0\n\t13.0,14.0,15.0,16.0\n]";
    EXPECT_EQ(std::string(expected), str(m, 1));
}

TEST(Mat4x4fTest, Mul) {
    float adata[16] = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0};
    float bdata[16] = {
        -2.0, 1.0, 2.0, 3.0,
        3.0, 2.0, 1.0, -1.0,
        4.0, 3.0, 6.0, 5.0,
        1.0, 2.0, 7.0, 8.0};
    float edata[16] = {
        20.0, 22.0, 50.0, 48.0,
        44.0, 54.0, 114.0, 108.0,
        40.0, 58.0, 110.0, 102.0,
        16.0, 26.0, 46.0, 42.0};
    Mat4x4f a(adata);
    Mat4x4f b(bdata);
    Mat4x4f e(edata);
    auto r = a * b;

    EXPECT_EQ(str(e), str(r));

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            EXPECT_FLOAT_EQ(r(row, col), e(row, col));
        }
    }

    EXPECT_EQ(a * b, e);
}

TEST(Mat4x4fTest, MulVec) {
    float data[16] = {
        1.0, 2.0, 3.0, 4.0,
        2.0, 4.0, 4.0, 2.0,
        8.0, 6.0, 4.0, 1.0,
        0.0, 0.0, 0.0, 1.0};
    Mat4x4f m(data);
    Vec4f v(1.0, 2.0, 3.0, 1.0);
    auto result = mul(m, v);
    Vec4f expected(18.0, 24.0, 33.0, 1.0);
    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(result.z, expected.z);
    EXPECT_FLOAT_EQ(result.w, expected.w);
    EXPECT_EQ(result, expected);
}

TEST(Mat4x4fTest, Identity) {
    auto id = Identity();
    auto a = Vec4f(1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(id * a, Vec4f(1.0, 2.0, 3.0, 4.0));

    float data[16] = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0};
    auto test = Mat4x4f(data);
    auto expected = Mat4x4f(data);
    EXPECT_EQ(test * id, expected);
}

TEST(Mat4x4fTest, Transpose) {
    float data[16] = {
        0.0, 9.0, 3.0, 0.0,
        9.0, 8.0, 0.0, 8.0,
        1.0, 8.0, 5.0, 3.0,
        0.0, 0.0, 5.0, 8.0};
    float transposeData[16] = {
        0.0, 9.0, 1.0, 0.0,
        9.0, 8.0, 8.0, 0.0,
        3.0, 0.0, 5.0, 5.0,
        0.0, 8.0, 3.0, 8.0};
    auto test = Mat4x4f(data);
    auto expected = Mat4x4f(transposeData);
    EXPECT_EQ(str(transpose<Mat4x4f>(test)), str(expected));
    EXPECT_EQ(transpose<Mat4x4f>(test), expected);
    auto id = Identity();
    EXPECT_EQ(transpose<Mat4x4f>(id), Identity());
}

TEST(Mat4x4fTest, Determinant) {
    float data[16] = {
        1.0, 5.0, 0.0, 0.0,
        -3.0, 2.0, 7.0, 0.0,
        0.0, 6.0, -3.0, 0.0,
        0.0, 0.0, 0.0, 0.0};
    auto test = Mat4x4f(data);
    EXPECT_FLOAT_EQ(determinant2x2(test, 0, 0), 17.0);
    EXPECT_FLOAT_EQ(determinant2x2(test, 1, 1), -48.0);
}

TEST(Mat4x4fTest, Submatrix) {
    float data[16] = {
        -6.0, 1.0, 1.0, 6.0,
        -8.0, 5.0, 8.0, 6.0,
        -1.0, 0.0, 8.0, 2.0,
        -7.0, 1.0, -1.0, 1.0};

    float expectedData[16] = {
        -6.0, 1.0, 6.0, 0.0,
        -8.0, 8.0, 6.0, 0.0,
        -7.0, -1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0};

    Mat4x4f m(data);
    Mat4x4f expected(expectedData);
    EXPECT_EQ(str(submatrix<Mat4x4f>(m, 2, 1)), str(expected));
}

TEST(Mat4x4fTest, MinorAndCofactor) {
    float data[16] = {
        3.0, 5.0, 0.0, 0.0,
        2.0, -1.0, -7.0, 0.0,
        6.0, -1.0, 5.0, 0.0,
        0.0, 0.0, 0.0, 0.0};
    auto test = Mat4x4f(data);
    EXPECT_FLOAT_EQ(minor3x3(test, 1, 0), 25.0);
    EXPECT_FLOAT_EQ(cofactor3x3(test, 1, 0), -25.0);
    EXPECT_FLOAT_EQ(minor3x3(test, 0, 0), -12.0);
    EXPECT_FLOAT_EQ(cofactor3x3(test, 0, 0), -12.0);
}

TEST(Mat4x4fTest, Determinant3x3) {
    float data[16] = {
        1.0, 2.0, 6.0, 0.0,
        -5.0, 8.0, -4.0, 0.0,
        2.0, 6.0, 4.0, 0.0,
        0.0, 0.0, 0.0, 0.0};
    auto test = Mat4x4f(data);
    EXPECT_FLOAT_EQ(cofactor3x3(test, 0, 0), 56.0);
    EXPECT_FLOAT_EQ(cofactor3x3(test, 0, 1), 12.0);
    EXPECT_FLOAT_EQ(cofactor3x3(test, 0, 2), -46.0);
    EXPECT_FLOAT_EQ(determinant3x3(test), -196.0);
    EXPECT_FLOAT_EQ(determinant3x3(test, 1), -196.0);
    EXPECT_FLOAT_EQ(determinant3x3(test, 2), -196.0);
}

TEST(Mat4x4fTest, Determinant4x4) {
    float data[16] = {
        -2.0, -8.0, 3.0, 5.0,
        -3.0, 1.0, 7.0, 3.0,
        1.0, 2.0, -9.0, 6.0,
        -6.0, 7.0, 7.0, -9.0};
    auto test = Mat4x4f(data);

    EXPECT_FLOAT_EQ(cofactor4x4(test, 0, 0), 690.0);
    EXPECT_FLOAT_EQ(cofactor4x4(test, 0, 1), 447.0);
    EXPECT_FLOAT_EQ(cofactor4x4(test, 0, 2), 210.0);
    EXPECT_FLOAT_EQ(cofactor4x4(test, 0, 3), 51.0);
    EXPECT_FLOAT_EQ(determinant4x4(test), -4071.0);
    EXPECT_FLOAT_EQ(determinant4x4(test, 1), -4071.0);
    EXPECT_FLOAT_EQ(determinant4x4(test, 2), -4071.0);
    EXPECT_FLOAT_EQ(determinant4x4(test, 3), -4071.0);
}

TEST(Mat4x4fTest, Invertible) {
    float data1[16] = {
        6.0, 4.0, 4.0, 4.0,
        5.0, 5.0, 7.0, 6.0,
        4.0, -9.0, 3.0, -7.0,
        9.0, 1.0, 7.0, -6.0};
    auto test1 = Mat4x4f(data1);
    float data2[16] = {
        -4.0, 2.0, -2.0, -3.0,
        9.0, 6.0, 2.0, 6.0,
        0.0, -5.0, 1.0, -5.0,
        0.0, 0.0, 0.0, 0.0};
    auto test2 = Mat4x4f(data2);

    EXPECT_TRUE(invertible(test1));
    EXPECT_FALSE(invertible(test2));
}

TEST(Mat4x4fTest, Inverse) {
    float data[16] = {
        -5.0, 2.0, 6.0, -8.0,
        1.0, -5.0, 1.0, 8.0,
        7.0, 7.0, -6.0, -7.0,
        1.0, -3.0, 7.0, 4.0};
    auto test = Mat4x4f(data);
    float expectedData[16] = {
        0.21805, 0.45113, 0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361, 0.52068,
        -0.07895, -0.22368, -0.05263, 0.19737,
        -0.52256, -0.81391, -0.30075, 0.30639};
    auto expected = Mat4x4f(expectedData);
    EXPECT_FLOAT_EQ(determinant4x4(test), 532.0);
    EXPECT_FLOAT_EQ(cofactor4x4(test, 3, 2), 105.0);
    EXPECT_EQ(str(expected, 5), str(inverse(test), 5));
}