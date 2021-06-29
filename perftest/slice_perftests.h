#pragma once
#include "anvil/containers/arrayutils.h"
#include "anvil/containers/slice.h"
#include "anvil/math/rand.h"
#include "anvil/types.h"
#include "testcase.h"

using namespace anvil::containers;

class SliceTest : public TestCase {
   public:
    SliceTest() = delete;
    SliceTest(const isize_t test_size) : m_test_size(test_size) {
        m_slice = new Slice<u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~SliceTest() {
        delete m_slice;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    isize_t m_test_size;
    Slice<u64_t>* m_slice;
    int* m_elements;
};

class SliceInsertTest : public SliceTest {
   public:
    SliceInsertTest(const isize_t test_size) : SliceTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            u64_t val = static_cast<u64_t>(anvil::math::rand());
            m_slice->Insert(val);
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class SliceSearchTest : public SliceTest {
   public:
    SliceSearchTest(const isize_t test_size) : SliceTest(test_size) {}
    void Setup() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            int val = anvil::math::rand();
            m_slice->Insert(val);
            m_elements[idx] = val;
        }
        scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            m_slice->IndexOf(m_elements[idx]);
        }
    }
    void TearDown() override {
        m_slice->Clear();
    }
};