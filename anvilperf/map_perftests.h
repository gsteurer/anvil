#pragma once

#include "ads/arrayutils.h"
#include "ads/map.h"
#include "rand.h"
#include "testcase.h"
#include "types.h"

class MapTest : public TestCase {
   public:
    MapTest() = delete;
    MapTest(const anvil::isize_t test_size) : m_test_size(test_size) {
        m_map = new Map<anvil::u64_t, anvil::u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~MapTest() {
        delete m_map;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    anvil::isize_t m_test_size;
    Map<anvil::u64_t, anvil::u64_t>* m_map;
    int* m_elements;
};

class MapInsertTest : public MapTest {
   public:
    MapInsertTest(const anvil::isize_t test_size) : MapTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            anvil::u64_t val = static_cast<anvil::u64_t>(anvil::rand());
            (*m_map)[val] = val;
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class MapSearchTest : public MapTest {
   public:
    MapSearchTest(const anvil::isize_t test_size) : MapTest(test_size) {}
    void Setup() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            int val = anvil::rand();
            (*m_map)[val] = val;
            m_elements[idx] = val;
        }
        anvil::scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (anvil::isize_t idx = 0; idx < m_test_size; idx++) {
            (*m_map)[m_elements[idx]];
        }
    }
    void TearDown() override {
        m_map->Clear();
    }
};