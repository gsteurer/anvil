#pragma once

#include "containers/arrayutils.h"
#include "containers/map.h"
#include "math/rand.h"
#include "testcase.h"
#include "types.h"

using namespace anvil::containers;

class MapTest : public TestCase {
   public:
    MapTest() = delete;
    MapTest(const isize_t test_size) : m_test_size(test_size) {
        m_map = new Map<u64_t, u64_t>();
        m_elements = new int[m_test_size];
    }
    virtual ~MapTest() {
        delete m_map;
        delete[] m_elements;
    }
    virtual void Setup() = 0;

    virtual void Execute() = 0;

    virtual void TearDown() = 0;

    isize_t m_test_size;
    Map<u64_t, u64_t>* m_map;
    int* m_elements;
};

class MapInsertTest : public MapTest {
   public:
    MapInsertTest(const isize_t test_size) : MapTest(test_size) {}
    void Setup() override {}
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            u64_t val = static_cast<u64_t>(rand());
            (*m_map)[val] = val;
            m_elements[idx] = val;
        }
    }
    void TearDown() override {}
};

class MapSearchTest : public MapTest {
   public:
    MapSearchTest(const isize_t test_size) : MapTest(test_size) {}
    void Setup() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            int val = rand();
            (*m_map)[val] = val;
            m_elements[idx] = val;
        }
        scramble(m_elements, m_test_size);
    }
    void Execute() override {
        for (isize_t idx = 0; idx < m_test_size; idx++) {
            (*m_map)[m_elements[idx]];
        }
    }
    void TearDown() override {
        m_map->Clear();
    }
};