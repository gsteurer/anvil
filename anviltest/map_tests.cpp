#include <string>

#include "ads/hash.h"
#include "ads/map.h"
#include "gtest/gtest.h"
#include "option.h"

struct Foo {
    Foo(int id) : id(id) {}
    Foo() {}
    Foo(const Foo& foo) : id(foo.id) {}
    bool operator==(const Foo& rhs) const { return this->id == rhs.id; }
    int id;
};

/* 
// need to implement hashable for foo or "symbols not found"
template <>
struct Hashable<Foo> {
    static long Hash(Foo key) {
        // @@@ FIXME
        return 55;
    }
};
*/

TEST(MapTests, MapEntry) {
    MapNode<int, int> test(5, 10);
    MapNode<int, int> test2(5, 15);
    MapNode<int, int> test3(6, 15);

    EXPECT_EQ(test, test2);
    EXPECT_NE(test, test3);

    MapNode<std::string, Foo> test4("foo", Foo(4));
}

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
    // result = Hashable<Foo>::Hash(Foo(99));
}

TEST(MapTests, Ctor) {
    Map<std::string, Foo> test;
    EXPECT_TRUE(test.Insert("foo", Foo(10)));
    EXPECT_TRUE(test.Insert("bar", Foo(20)));
    EXPECT_TRUE(test.Insert("baz", Foo(30)));
    Option<Foo> item = test["foo"];
    EXPECT_EQ(item.result, Option<Foo>::Some);
    EXPECT_EQ(item.value, Foo(10));
    EXPECT_FALSE(test.Insert("foo", Foo(20)));

    item = test.Remove("bar");
    EXPECT_EQ(item.result, Option<Foo>::Some);
    EXPECT_EQ(item.value, Foo(20));

    item = test.Remove("bar");
    EXPECT_EQ(item.result, Option<Foo>::None);
}
