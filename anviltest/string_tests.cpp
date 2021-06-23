#include "gtest/gtest.h"
#include "string/string.h"

TEST(StringTests, CtorCppString) {
    const char* expected = "The Quick Brown Fox Jumps Over The Angry Dog.";
    std::string target(expected);
    String s(target);

    EXPECT_STREQ(expected, s.cstr());
    EXPECT_TRUE(streq(expected, s.cstr()));
}