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
    int size = 16;
    long result = Hashable<int>::Hash(55);
    int key = result & (size - 1);
    EXPECT_EQ(key, 7);
    // @@@ this should produce a compiler error unless we impl hashable
    // result = Hashable<Foo>::Hash(Foo(99));
}