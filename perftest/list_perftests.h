#pragma once

#include "anvil/containers/arrayutils.h"
#include "anvil/containers/list.h"
#include "anvil/math/rand.h"
#include "anvil/types.h"
#include "testcase.h"

using namespace anvil::containers;

class ListTest : public TestCase {
   public:
    ListTest() = delete;
    ListTest(const isize_t test_size) : m_test_size(test_size) {
        m_list = new List<u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~ListTest() {
        delete m_list;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    isize_t m_test_size;
    List<u64_t>* m_list;
    int* m_elements;
};

class ListInsertTest : public ListTest {
   public:
    ListInsertTest(const isize_t test_size) : ListTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            u64_t val = static_cast<u64_t>(anvil::math::rand());
            m_list->PushFront(val);
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class ListSearchTest : public ListTest {
   public:
    ListSearchTest(const isize_t test_size) : ListTest(test_size) {}
    void Setup() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            int val = anvil::math::rand();
            m_list->PushFront(val);
            m_elements[idx] = val;
        }
        scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            m_list->IndexOf(m_elements[idx]);
        }
    }
    void TearDown() override {
        m_list->Clear();
    }
};