#include <stdio.h>

#include <cmath>

#include "anvil/containers/redblacktree.h"
#include "anvil/option.h"
#include "foo.h"
#include "gtest/gtest.h"

using namespace anvil::containers;

template <typename T>
::testing::AssertionResult verifySentinel(RBTree<T>* tree) {
    if (tree->m_sentinel->color != RBNode<T>::BLACK) {
        return ::testing::AssertionFailure() << "got " << str<T>(tree->m_sentinel->color) << " expected " << str<T>(RBNode<T>::BLACK);
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
    ASSERT_TRUE(node->color == RBNode<T>::RED || node->color == RBNode<T>::BLACK);
    // root is black
    ASSERT_TRUE(tree->m_root->color == RBNode<T>::BLACK);
    // every leaf is black
    if (node->left == tree->m_sentinel) {
        ASSERT_TRUE(node->left->color == RBNode<T>::BLACK);
    }
    if (node->right == tree->m_sentinel) {
        ASSERT_TRUE(node->right->color == RBNode<T>::BLACK);
    }
    // if a node is red, both children are black
    if (node->color == RBNode<T>::RED) {
        ASSERT_TRUE(node->left->color == RBNode<T>::BLACK);
        ASSERT_TRUE(node->right->color == RBNode<T>::BLACK);
    }

    if (node->left != tree->m_sentinel) {
        checkRedBlackProperties(tree, node->left);
    }
    if (node->right != tree->m_sentinel) {
        checkRedBlackProperties(tree, node->right);
    }
}

TEST(RedBlackTreeTest, Ctor) {
    RBTree<int>* tree = new RBTree<int>();

    delete tree;
}

TEST(RedBlackTreeTest, InsertOne) {
    RBTree<int>* tree = new RBTree<int>();
    tree->Insert(1);
    delete tree;
}

TEST(RedBlackTreeTest, InsertOneCompound) {
    RBTree<Foo<int>>* tree = new RBTree<Foo<int>>();
    tree->Insert(1);
    delete tree;
}

TEST(RedBlackTreeTest, InsertMulti) {
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
    delete tree;
}

TEST(RedBlackTreeTest, InsertLarge) {
    RBTree<Foo<int>>* tree = new RBTree<Foo<int>>();
    int size = 1000;
    // adding seventh leaks
    for (int idx = 0; idx < size; idx++) {
        tree->Insert(Foo<int>(idx + 1));
        EXPECT_TRUE(verifySentinel(tree));
        Option<Foo<int>> result = tree->Search(Foo<int>(idx + 1));
        EXPECT_EQ(result.result, Option<Foo<int>>::Some);
        EXPECT_EQ(result.value.ID(), idx + 1);
    }

    for (int idx = 0; idx < size; idx++) {
        Option<Foo<int>> result = tree->Search(Foo<int>(idx + 1));
        EXPECT_EQ(result.result, Option<Foo<int>>::Some);
        EXPECT_EQ(result.value.ID(), idx + 1);
    }
    // https://www.codesdope.com/course/data-structures-red-black-trees/
    // https://www.baeldung.com/cs/binary-tree-height
    // https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
    EXPECT_TRUE(tree->Height() <= 2 * (std::log(size + 1) / std::log(2)));
    checkRedBlackProperties(tree, tree->m_root);
    EXPECT_EQ(tree->Min(), Foo<int>(1));
    EXPECT_EQ(tree->Max(), Foo<int>(size));

    delete tree;
}

TEST(RedBlackTreeTest, Delete) {
    RBTree<Foo<int>>* tree = new RBTree<Foo<int>>();
    int size = 1000;

    for (int idx = 0; idx < size; idx++) {
        tree->Insert(Foo<int>(idx + 1));
    }

    EXPECT_EQ(tree->Size(), size);
    for (int idx = 0; idx < size; idx++) {
        tree->Delete(idx + 1);
        Option<Foo<int>> result = tree->Search(Foo<int>(idx + 1));
        EXPECT_EQ(result.result, Option<Foo<int>>::None);
    }
    EXPECT_EQ(tree->Size(), 0);

    delete tree;
}