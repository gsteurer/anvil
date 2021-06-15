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

TEST(MapTests, Ctor) {
    Map<int, int> test;
    test.Insert(5, 10);
    int result = Hashable<int>::Hash(5);
    EXPECT_EQ(result, 55);
    // @@@ this should produce a compiler error unless we impl hashable
    // result = Hashable<Foo>::Hash(Foo(99));
}