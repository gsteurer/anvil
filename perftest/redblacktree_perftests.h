#pragma once

#include "anvil/containers/arrayutils.h"
#include "anvil/containers/redblacktree.h"
#include "anvil/math/rand.h"
#include "anvil/types.h"
#include "testcase.h"

using namespace anvil::containers;

class RBTreeTest : public TestCase {
   public:
    RBTreeTest() = delete;
    RBTreeTest(const isize_t test_size) : m_test_size(test_size) {
        m_tree = new RBTree<u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~RBTreeTest() {
        delete m_tree;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    isize_t m_test_size;
    RBTree<u64_t>* m_tree;
    int* m_elements;
};

class RBTreeInsertTest : public RBTreeTest {
   public:
    RBTreeInsertTest(const isize_t test_size) : RBTreeTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            u64_t val = static_cast<u64_t>(anvil::math::rand());
            m_tree->Insert(val);
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class RBTreeSearchTest : public RBTreeTest {
   public:
    RBTreeSearchTest(const isize_t test_size) : RBTreeTest(test_size) {}
    void Setup() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            int val = anvil::math::rand();
            m_tree->Insert(val);
            m_elements[idx] = val;
        }
        scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            m_tree->Search(m_elements[idx]);
        }
    }
    void TearDown() override {
        m_tree->Clear();
    }
};