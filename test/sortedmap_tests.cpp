#include <string>

#include "anvil/containers/sortedmap.h"
#include "anvil/option.h"
#include "foo.h"
#include "gtest/gtest.h"
using namespace anvil::containers;

TEST(SortedMapTests, Ctor) {
    SortedMap<std::string, Foo<int>> test;
    EXPECT_EQ(test.Size(), 0);
}

TEST(SortedMapTests, InsertAndRemove) {
    SortedMap<std::string, Foo<int>> test;

    // get item that isn't in the map
    Option<Foo<int>> result = test["foo"];
    EXPECT_EQ(Option<Foo<int>>::None, result.result);
    EXPECT_EQ(0, test.Size());

    //insert an item, size increases
    EXPECT_TRUE(test.Insert("foo", Foo<int>(69)));
    EXPECT_EQ(1, test.Size());

    //try to insert a duplicate of the item
    EXPECT_FALSE(test.Insert("foo", Foo<int>(69)));
    EXPECT_EQ(1, test.Size());

    // use bracket to get an item
    result = test["foo"];
    EXPECT_EQ(Option<Foo<int>>::Some, result.result);
    EXPECT_EQ(Foo<int>(69).ID(), result.value);

    // remove an inserted item
    result = test.Remove("foo");
    EXPECT_EQ(Option<Foo<int>>::Some, result.result);
    EXPECT_EQ(Foo<int>(69), result.value);
    EXPECT_EQ(0, test.Size());

    // remove a deleted item
    result = test.Remove("foo");
    EXPECT_EQ(Option<Foo<int>>::None, result.result);
    EXPECT_EQ(0, test.Size());

    // use brack to insert an item
    test["foo"] = Foo<int>(69);
    result = test["foo"];
    EXPECT_EQ(Option<Foo<int>>::Some, result.result);
    EXPECT_EQ(Foo<int>(69), result.value);
}
