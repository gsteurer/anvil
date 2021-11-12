#include "anvil/string/cstring.h"
#include "anvil/string/stlutils.h"
#include "anvil/types.h"
#include "gtest/gtest.h"

using namespace anvil::string;

TEST(StringTests, Operations) {
    // length
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    EXPECT_EQ(anvil::string::strlen(expected), 45);

    // reverse
    const char* expected2 = "Foobar!";
    const char* expected2_reversed = "!rabooF";
    char* test = strrev(expected2);
    EXPECT_STREQ(expected2_reversed, test);
    EXPECT_EQ(anvil::string::strlen(expected2), 7);  // will segfault if str is not null terminated
    delete[] test;

    // equal
    EXPECT_TRUE(streq(expected, expected));
    EXPECT_FALSE(streq(expected, expected2));
}

TEST(StringTests, Copy) {
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    char* test = nullptr;
    isize_t size;
    strcpy(expected, &test, &size);
    EXPECT_STREQ(expected, test);
    EXPECT_EQ(anvil::string::strlen(expected), anvil::string::strlen(test));
    delete[] test;
}

TEST(StringTests, IntegerToStr) {
    char* test;
    i64_t a = -123456789011121314;
    const char* astr = "-123456789011121314";
    test = itoa(a);
    EXPECT_STREQ(astr, test);
    delete[] test;

    u64_t b = 678901234567890;
    const char* bstr = "678901234567890";
    test = itoa(b);
    EXPECT_STREQ(bstr, test);
    delete[] test;

    i32_t c = -65535;
    const char* cstr = "-65535";
    test = itoa(c);
    EXPECT_STREQ(cstr, test);
    delete[] test;

    u32_t d = 65536;
    const char* dstr = "65536";
    test = itoa(d);
    EXPECT_STREQ(dstr, test);
    delete[] test;
}

TEST(StringTests, FloatToStr) {
    char* test;
    f64_t a = 271.829;  //2.7182818284590452353602874713527;
    // const char* astr = "2.7182818284590452353602874713527";
    // const char* expected = "271.829";
    test = ftoa(a, 5);
    // @@@ EXPECT_STREQ(expected, test);
    delete[] test;
}

TEST(StringTests, CtorCppString) {
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    String s(expected);
    EXPECT_STREQ(expected, s.cstr());
    EXPECT_TRUE(streq(expected, s.cstr()));
}

TEST(StringTests, STLUtilsStrip) {
    const char* expected = "foo bar baz qux quux";
    std::string sample = "foo bar baz qux quux";
    auto result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ(expected, result.c_str());

    sample = " foo bar baz qux quux ";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ(expected, result.c_str());

    sample = " foo bar baz qux quux";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ(expected, result.c_str());

    sample = "foo bar baz qux quux ";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ(expected, result.c_str());

    sample = " \t\nfoo bar baz qux quux\v ";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ(expected, result.c_str());

    sample = "\n\n\nfoo bar baz qux quux";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ(expected, result.c_str());

    sample = " ";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ("", result.c_str());

    sample = " \t\n\v\f";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ("", result.c_str());

    sample = "";
    result = anvil::string::stlutils::strip(sample);
    EXPECT_STREQ("", result.c_str());
}

TEST(StringTests, STLUtilsSplit) {
    std::string sample = "foo bar baz qux quux";
    std::string delim = " ";
    auto result = anvil::string::stlutils::split(sample, delim);
    EXPECT_EQ(static_cast<size_t>(5), result.size());
    EXPECT_STREQ("foo", result[0].c_str());
    EXPECT_STREQ("bar", result[1].c_str());
    EXPECT_STREQ("baz", result[2].c_str());
    EXPECT_STREQ("qux", result[3].c_str());
    EXPECT_STREQ("quux", result[4].c_str());

    sample = "afoobfoocfoofoofoo";
    delim = "foo";
    result = anvil::string::stlutils::split(sample, delim);
    EXPECT_EQ(static_cast<size_t>(6), result.size());
    EXPECT_STREQ("a", result[0].c_str());
    EXPECT_STREQ("b", result[1].c_str());
    EXPECT_STREQ("c", result[2].c_str());
    EXPECT_STREQ("", result[3].c_str());
    EXPECT_STREQ("", result[4].c_str());
    EXPECT_STREQ("", result[5].c_str());

    sample = "1//2";
    delim = "/";
    result = anvil::string::stlutils::split(sample, delim);
    EXPECT_EQ(static_cast<size_t>(3), result.size());
    EXPECT_STREQ("1", result[0].c_str());
    EXPECT_STREQ("", result[1].c_str());
    EXPECT_STREQ("2", result[2].c_str());

    sample = "1";
    delim = "/";
    result = anvil::string::stlutils::split(sample, delim);
    EXPECT_EQ(static_cast<size_t>(1), result.size());
    EXPECT_STREQ("1", result[0].c_str());
}
