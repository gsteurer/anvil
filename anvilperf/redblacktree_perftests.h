#pragma once

#include "ads/arrayutils.h"
#include "ads/redblacktree.h"
#include "rand.h"
#include "testcase.h"
#include "types.h"

class RBTreeTest : public TestCase {
   public:
    RBTreeTest() = delete;
    RBTreeTest(const anvil::isize_t test_size) : m_test_size(test_size) {
        m_tree = new RBTree<anvil::u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~RBTreeTest() {
        delete m_tree;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    anvil::isize_t m_test_size;
    RBTree<anvil::u64_t>* m_tree;
    int* m_elements;
};

class RBTreeInsertTest : public RBTreeTest {
   public:
    RBTreeInsertTest(const anvil::isize_t test_size) : RBTreeTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            anvil::u64_t val = static_cast<anvil::u64_t>(anvil::rand());
            m_tree->Insert(val);
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class RBTreeSearchTest : public RBTreeTest {
   public:
    RBTreeSearchTest(const anvil::isize_t test_size) : RBTreeTest(test_size) {}
    void Setup() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            int val = anvil::rand();
            m_tree->Insert(val);
            m_elements[idx] = val;
        }
        anvil::scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            m_tree->Search(m_elements[idx]);
        }
    }
    void TearDown() override {
        m_tree->Clear();
    }
};