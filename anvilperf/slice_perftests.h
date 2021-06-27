#pragma once
#include "ads/arrayutils.h"
#include "ads/slice.h"
#include "rand.h"
#include "testcase.h"
#include "types.h"

class SliceTest : public TestCase {
   public:
    SliceTest() = delete;
    SliceTest(const anvil::isize_t test_size) : m_test_size(test_size) {
        m_slice = new anvil::Slice<anvil::u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~SliceTest() {
        delete m_slice;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    anvil::isize_t m_test_size;
    anvil::Slice<anvil::u64_t>* m_slice;
    int* m_elements;
};

class SliceInsertTest : public SliceTest {
   public:
    SliceInsertTest(const anvil::isize_t test_size) : SliceTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            anvil::u64_t val = static_cast<anvil::u64_t>(anvil::rand());
            m_slice->Insert(val);
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class SliceSearchTest : public SliceTest {
   public:
    SliceSearchTest(const anvil::isize_t test_size) : SliceTest(test_size) {}
    void Setup() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            int val = anvil::rand();
            m_slice->Insert(val);
            m_elements[idx] = val;
        }
        anvil::scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            m_slice->IndexOf(m_elements[idx]);
        }
    }
    void TearDown() override {
        m_slice->Clear();
    }
};