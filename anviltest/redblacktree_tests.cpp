#include <stdio.h>

#include "ads/redblacktree.h"
#include "gtest/gtest.h"

struct Foo {
    Foo() : id(0) {}
    Foo(int id) : id(id) {}
    bool operator<(const Foo& foo) { return id < foo.id; };
    bool operator==(const Foo& foo) { return id == foo.id; };
    bool operator!=(const Foo& foo) { return !(id == foo.id); };
    int id;
};
RBTree<Foo> _;

::testing::AssertionResult verifySentinel(RBTree<int>* tree) {
    if (tree->m_sentinel->color != BLACK) {
        return ::testing::AssertionFailure() << "got " << str(tree->m_sentinel->color) << " expected " << str(BLACK);
    }
    if (tree->m_sentinel->parent != tree->m_sentinel) {
        return ::testing::AssertionFailure() << "expected tree->m_sentinel for parent got " << tree->m_sentinel->parent;
    }
    if (tree->m_sentinel->left != tree->m_sentinel) {
        return ::testing::AssertionFailure() << "expected tree->m_sentinel for left got " << tree->m_sentinel->left;
    }
    if (tree->m_sentinel->right != tree->m_sentinel) {
        return ::testing::AssertionFailure() << "expected tree->m_sentinel for right got " << tree->m_sentinel->right;
    }
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult verifyInsert(RBTree<int>* tree, int item) {
    int* result = tree->Search(item);
    if (result != nullptr) {
        if (*result == item) {
            return ::testing::AssertionSuccess();
        }
    }
    return ::testing::AssertionFailure() << item << " not found ";
}

TEST(RedBlackTreeTest, Insert) {
    EXPECT_TRUE(true);
    RBTree<int>* tree = new RBTree<int>();
    RBNode<int>* node;
    RBNode<int>* sentinel = tree->m_sentinel;
    EXPECT_TRUE(verifySentinel(tree));
    tree->Insert(1);
    EXPECT_TRUE(verifySentinel(tree));
    EXPECT_TRUE(verifyInsert(tree, 1));
    tree->Insert(2);
    tree->Search(2);
    node = tree->m_root;
    EXPECT_NE(node, sentinel);
    EXPECT_EQ(node->key, 1);
    EXPECT_NE(node, sentinel);
    EXPECT_EQ(node->right->key, 2);
    EXPECT_NE(node->right, sentinel);

    EXPECT_TRUE(verifySentinel(tree));
    EXPECT_TRUE(verifyInsert(tree, 1));
    EXPECT_TRUE(verifyInsert(tree, 2));
}

TEST(RedBlackTreeTest, Ctor) {
    EXPECT_TRUE(true);
    RBTree<int>* tree = new RBTree<int>();
    int size = 1000;

    for (int idx = 0; idx < size; idx++) {
        tree->Insert(idx + 1);
        EXPECT_TRUE(verifySentinel(tree));
        int* result = tree->Search(idx + 1);
        EXPECT_TRUE(result != nullptr);
    }

    for (int idx = 0; idx < size; idx++) {
        int* result = tree->Search(idx + 1);
        EXPECT_NE(result, nullptr);
        if (result != nullptr) {
            EXPECT_EQ(*result, idx + 1);
        }
    }
}
