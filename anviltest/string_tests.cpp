#include "gtest/gtest.h"
#include "string/string.h"
#include "types.h"

TEST(StringTests, Operations) {
    // length
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    EXPECT_EQ(anvil::strlen(expected), 45);

    // reverse
    const char* expected2 = "Foobar!";
    const char* expected2_reversed = "!rabooF";
    char* test = anvil::strrev(expected2);
    EXPECT_STREQ(expected2_reversed, test);
    EXPECT_EQ(anvil::strlen(expected2), 7);  // will segfault if str is not null terminated
    delete[] test;

    // equal
    EXPECT_TRUE(anvil::streq(expected, expected));
    EXPECT_FALSE(anvil::streq(expected, expected2));
}

TEST(StringTests, Copy) {
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    char* test = nullptr;
    anvil::isize_t size;
    anvil::strcpy(expected, &test, &size);
    EXPECT_STREQ(expected, test);
    EXPECT_EQ(anvil::strlen(expected), anvil::strlen(test));
}

TEST(StringTests, IntegerToStr) {
    char* test;
    anvil::i64_t a = -123456789011121314;
    const char* astr = "-123456789011121314";
    test = anvil::itoa(a);
    EXPECT_STREQ(astr, test);
    delete[] test;

    anvil::u64_t b = 678901234567890;
    const char* bstr = "678901234567890";
    test = anvil::itoa(b);
    EXPECT_STREQ(bstr, test);
    delete[] test;

    anvil::i32_t c = -65535;
    const char* cstr = "-65535";
    test = anvil::itoa(c);
    EXPECT_STREQ(cstr, test);
    delete[] test;

    anvil::u32_t d = 65536;
    const char* dstr = "65536";
    test = anvil::itoa(d);
    EXPECT_STREQ(dstr, test);
    delete[] test;
}

TEST(StringTests, FloatToStr) {
    char* test;
    anvil::f64_t a = 271.829;  //2.7182818284590452353602874713527;
    // const char* astr = "2.7182818284590452353602874713527";
    // const char* expected = "271.829";
    test = anvil::ftoa(a, 5);
    // @@@ EXPECT_STREQ(expected, test);
    delete[] test;
}

TEST(StringTests, CtorCppString) {
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    anvil::String s(expected);
    EXPECT_STREQ(expected, s.cstr());
    EXPECT_TRUE(anvil::streq(expected, s.cstr()));
}
