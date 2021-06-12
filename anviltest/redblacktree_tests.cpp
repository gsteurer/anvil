#include <stdio.h>

#include <cmath>

#include "ads/redblacktree.h"
#include "gtest/gtest.h"
#include "option.h"

struct Foo {
    Foo() : id(0) {}
    Foo(int id) : id(id) {}
    bool operator<(const Foo& foo) { return id < foo.id; };
    bool operator==(const Foo& foo) const { return id == foo.id; };
    bool operator!=(const Foo& foo) { return !(id == foo.id); };
    int id;
};

template <typename T>
::testing::AssertionResult verifySentinel(RBTree<T>* tree) {
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

template <typename T>
inline void checkRedBlackProperties(RBTree<T>* tree, RBNode<T>* node) {
    // every node is red or black
    ASSERT_TRUE(node->color == RED || node->color == BLACK);
    // root is black
    ASSERT_TRUE(tree->m_root->color == BLACK);
    // every leaf is black
    if (node->left == tree->m_sentinel) {
        ASSERT_TRUE(node->left->color == BLACK);
    }
    if (node->right == tree->m_sentinel) {
        ASSERT_TRUE(node->right->color == BLACK);
    }
    // if a node is red, both children are black
    if (node->color == RED) {
        ASSERT_TRUE(node->left->color == BLACK);
        ASSERT_TRUE(node->right->color == BLACK);
    }

    if (node->left != tree->m_sentinel) {
        checkRedBlackProperties(tree, node->left);
    }
    if (node->right != tree->m_sentinel) {
        checkRedBlackProperties(tree, node->right);
    }
}

TEST(RedBlackTreeTest, Insert) {
    RBTree<int>* tree = new RBTree<int>();
    RBNode<int>* node;
    RBNode<int>* sentinel = tree->m_sentinel;
    EXPECT_TRUE(verifySentinel(tree));
    tree->Insert(1);
    EXPECT_TRUE(verifySentinel(tree));
    Option<int> result = tree->Search(1);
    EXPECT_EQ(result.value, 1);
    tree->Insert(2);
    result = tree->Search(2);
    EXPECT_EQ(result.result, Option<int>::Some);
    EXPECT_EQ(result.value, 2);
    node = tree->m_root;
    EXPECT_NE(node, sentinel);
    EXPECT_EQ(node->key, 1);
    EXPECT_NE(node, sentinel);
    EXPECT_EQ(node->right->key, 2);
    EXPECT_NE(node->right, sentinel);

    EXPECT_TRUE(verifySentinel(tree));
}

TEST(RedBlackTreeTest, InsertLarge) {
    RBTree<Foo>* tree = new RBTree<Foo>();
    int size = 1000;

    for (int idx = 0; idx < size; idx++) {
        tree->Insert(Foo(idx + 1));
        EXPECT_TRUE(verifySentinel(tree));
        Option<Foo> result = tree->Search(Foo(idx + 1));
        EXPECT_EQ(result.result, Option<Foo>::Some);
        EXPECT_EQ(result.value.id, idx + 1);
    }

    for (int idx = 0; idx < size; idx++) {
        Option<Foo> result = tree->Search(Foo(idx + 1));
        EXPECT_EQ(result.result, Option<Foo>::Some);
        EXPECT_EQ(result.value.id, idx + 1);
    }
    // https://www.codesdope.com/course/data-structures-red-black-trees/
    // https://www.baeldung.com/cs/binary-tree-height
    // https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
    EXPECT_TRUE(tree->Height() <= 2 * (std::log(size + 1) / std::log(2)));
    checkRedBlackProperties(tree, tree->m_root);
    EXPECT_EQ(tree->Min(), Foo(1));
    EXPECT_EQ(tree->Max(), Foo(size));
}

TEST(RedBlackTreeTest, Delete) {
    RBTree<Foo>* tree = new RBTree<Foo>();
    int size = 1000;

    for (int idx = 0; idx < size; idx++) {
        tree->Insert(Foo(idx + 1));
    }

    EXPECT_EQ(tree->Size(), size);
    for (int idx = 0; idx < size; idx++) {
        tree->Delete(idx + 1);
        Option<Foo> result = tree->Search(Foo(idx + 1));
        EXPECT_EQ(result.result, Option<Foo>::None);
    }
    EXPECT_EQ(tree->Size(), 0);
}