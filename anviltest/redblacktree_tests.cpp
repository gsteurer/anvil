#include "ads/redblacktree.h"
#include "gtest/gtest.h"

struct Foo {
    Foo() : id(0) {}
    Foo(int id) : id(id) {}
    bool operator<(const Foo& foo) { return id < foo.id; };
    int id;
};

TEST(RedBlackTreeTest, Ctor) {
    EXPECT_TRUE(true);
    RBTree<Foo> tree;
    tree.Insert(Foo(1));
}
