#include "ads/graph.h"
#include "gtest/gtest.h"

TEST(GraphTest, Ctor) {
    anvil::Graph g;
    EXPECT_EQ(g.m_size, 0);
}
