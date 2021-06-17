#include "ads/hash.h"
#include "ads/map.h"
#include "gtest/gtest.h"
#include "option.h"

struct Foo {
    Foo(int id) : id(id) {}
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
    MapEntry<int, int> test(5, 10);
    MapEntry<int, int> test2(5, 15);
    MapEntry<int, int> test3(6, 15);

    EXPECT_EQ(test, test2);
    EXPECT_NE(test, test3);
}

TEST(MapTests, Ctor) {
    Map<int, int> test;
    test.Insert(5, 10);
    // @@@ this should produce a compiler error unless we impl hashable
    // result = Hashable<Foo>::Hash(Foo(99));
}

TEST(MapTests, Hash) {
    int size = 16;
    long result = Hashable<int>::Hash(55);
    int key = result & (size - 1);
    EXPECT_EQ(key, 7);

    result = Hashable<std::string>::Hash(std::string("foo"));

    //(((5381<<5)+5381)+102)
    //((177675<<5)+177675)+111
    //((5863386<<5)+5863386)+111
    EXPECT_EQ(result, 193491849);
}