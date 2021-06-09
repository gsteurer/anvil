#include "ads/redblacktree.h"
#include "gtest/gtest.h"

struct Foo {
    Foo() : id(0) {}
    Foo(int id) : id(id) {}
    bool operator<(const Foo& foo) { return id < foo.id; };
    int id;
};
RBTree<Foo> _;

TEST(RedBlackTreeTest, Ctor) {
    EXPECT_TRUE(true);
    RBTree<Foo> tree;
    for (int idx = 0; idx < 100; idx++) {
        tree.Insert(Foo(idx));
    }
}
