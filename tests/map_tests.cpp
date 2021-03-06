#include <string>

#include "anvil/containers/hash.h"
#include "anvil/containers/map.h"
#include "anvil/option.h"
#include "foo.h"
#include "gtest/gtest.h"

using namespace anvil::containers;

TEST(MapTests, Hash) {
    int size = 16;
    long result = Hashable<int>::Hash(55);
    int key = result & (size - 1);
    EXPECT_LE(key, size);

    result = Hashable<std::string>::Hash(std::string("foo"));

    //(((5381<<5)+5381)+102)
    //((177675<<5)+177675)+111
    //((5863386<<5)+5863386)+111
    EXPECT_EQ(result, 193491849);

    // @@@ this should produce a compiler error unless we impl hashable
    // result = Hashable<Foo<int>>::Hash(Foo<int>(99));
}

TEST(MapTests, Ctor) {
    Map<std::string, Foo<int>> test;
    EXPECT_TRUE(test.Insert("foo", Foo<int>(10)));
    EXPECT_TRUE(test.Insert("bar", Foo<int>(20)));
    EXPECT_TRUE(test.Insert("baz", Foo<int>(30)));
    Option<Foo<int>> item = test["foo"];
    EXPECT_EQ(item.result, Option<Foo<int>>::Some);
    EXPECT_EQ(item.value, Foo<int>(10));
    EXPECT_FALSE(test.Insert("foo", Foo<int>(20)));

    item = test["qux"];
    EXPECT_EQ(item.result, Option<Foo<int>>::None);

    Option<Foo<int>> removed = test.Remove("bar");
    EXPECT_EQ(removed.result, Option<Foo<int>>::Some);
    EXPECT_EQ(removed.value, Foo<int>(20));

    removed = test.Remove("bar");
    EXPECT_EQ(removed.result, Option<Foo<int>>::None);
}

TEST(MapTests, Bracket) {
    Map<std::string, Foo<int>> test;
    test["bar"] = Foo<int>(1);
    Option<Foo<int>> removed = test.Remove("bar");
    EXPECT_EQ(removed.result, Option<Foo<int>>::Some);
    EXPECT_EQ(removed.value, Foo<int>(1));
    test["foo"] = Foo<int>(2);
    Option<Foo<int>> item = test["foo"];
    EXPECT_EQ(item.result, Option<Foo<int>>::Some);
    EXPECT_EQ(item.value, Foo<int>(2));
    item = test["bar"];
    EXPECT_EQ(item.result, Option<Foo<int>>::None);
}

TEST(MapTests, Resize) {
    Map<std::string, Foo<int>> test;
    const int size = 1000;
    int data[size];
    EXPECT_EQ(test.Capacity(), 16);

    for (int idx = 0; idx < size; idx++) {
        int v = idx;
        std::string k = std::to_string(v);
        test[k] = Foo<int>(v);
        data[idx] = v;
    }

    EXPECT_LT(test.LoadFactor(), test.Threshold());

    for (int idx = 0; idx < size; idx++) {
        int v = data[idx];
        std::string k = std::to_string(v);
        Option<Foo<int>> item = test[k];
        EXPECT_EQ(item.result, Option<Foo<int>>::Some);
        EXPECT_EQ(item.value, Foo<int>(v));
    }

    EXPECT_GT(test.Capacity(), 16);
    EXPECT_LT(test.Size(), test.Capacity());
    EXPECT_EQ(test.Size(), size);
}

TEST(MapTests, InsertDuplicates) {
    Map<std::string, Foo<int>> test;
    test.Insert("foo", Foo<int>(5));
    EXPECT_EQ(test.Size(), 1);
    test.Insert("foo", Foo<int>(6));
    EXPECT_EQ(test.Size(), 1);
    Option<Foo<int>> result = test["foo"];
    EXPECT_EQ(result.result, Option<Foo<int>>::Some);
    EXPECT_EQ(result.value, Foo<int>(5));
}