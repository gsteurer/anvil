#include "containers/graph.h"
#include "gtest/gtest.h"

TEST(GraphTest, Ctor) {
    anvil::containers::Graph g;
    EXPECT_EQ(g.m_size, 0);
}
