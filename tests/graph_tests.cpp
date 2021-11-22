#include "anvil/containers/graph.h"
#include "gtest/gtest.h"

using namespace anvil::containers;
typedef Graph<int> TEST_GRAPH_T;
typedef Graph<int>::Vertex TEST_GRAPH_VERTEX_T;
typedef Option<Graph<int>::Vertex> TEST_GRAPH_OPTION_T;

TEST(GraphTest, CreateGetInsertRemove) {
    TEST_GRAPH_T test;
    TEST_GRAPH_OPTION_T result = test.GetVertex(12);
    EXPECT_EQ(TEST_GRAPH_OPTION_T::None, result.result);

    TEST_GRAPH_VERTEX_T testvert(12, 25);
    test.AddVertex(testvert);

    result = test.GetVertex(12);
    EXPECT_EQ(TEST_GRAPH_OPTION_T::Some, result.result);
    EXPECT_EQ(25, result.value.data);

    test.RemoveVertex(12);
    result = test.GetVertex(12);
    EXPECT_EQ(TEST_GRAPH_OPTION_T::None, result.result);
}
