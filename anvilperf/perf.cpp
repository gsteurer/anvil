#include <stdio.h>
#include <time.h>

#include "anvil/types.h"
#include "map_perftests.h"
#include "redblacktree_perftests.h"
#include "slice_perftests.h"
#include "testresult.h"

static const isize_t TEST_SIZE = 1000;
static const isize_t ITERATIONS = 10;

#define STR(x) #x

template <typename T>
struct TestRun {
    TestRun() = delete;
    TestRun(isize_t test_size, isize_t num_iterations) {
        m_buffer = new char[512];
        T test(test_size);
        for (isize_t idx = 0; idx < num_iterations; idx++) {
            m_result = test.Run();
        }
    }
    ~TestRun() {
        delete[] m_buffer;
    }
    char* to_str(char* buffer) {
        sprintf(buffer, "%s", m_result.to_str(buffer));
        return buffer;
    }
    char* m_buffer;
    TestResult m_result;
};

int main() {
    char* buffer = new char[512];
    /*
        Slice
    */
    TestRun<SliceSearchTest> sliceSearchTest(TEST_SIZE, ITERATIONS);
    printf("%s: %s\n", STR(SliceSearchTest), sliceSearchTest.to_str(buffer));

    TestRun<SliceInsertTest> sliceInsertTest(TEST_SIZE, ITERATIONS);
    printf("%s: %s\n", STR(SliceInsertTest), sliceInsertTest.to_str(buffer));

    /*
        Tree
    */
    TestRun<RBTreeSearchTest> rbtreeSearchTest(TEST_SIZE, ITERATIONS);
    printf("%s: %s\n", STR(RBTreeSearchTest), rbtreeSearchTest.to_str(buffer));

    TestRun<RBTreeInsertTest> rbtreeInsertTest(TEST_SIZE, ITERATIONS);
    printf("%s: %s\n", STR(RBTreeInsertTest), rbtreeInsertTest.to_str(buffer));

    /*
        Map
    */
    TestRun<MapSearchTest> mapSearchTest(TEST_SIZE, ITERATIONS);
    printf("%s: %s\n", STR(MapSearchTest), mapSearchTest.to_str(buffer));

    TestRun<MapInsertTest> mapInsertTest(TEST_SIZE, ITERATIONS);
    printf("%s: %s\n", STR(MapInsertTest), mapInsertTest.to_str(buffer));
    delete[] buffer;
}
