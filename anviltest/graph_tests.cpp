#include "gtest/gtest.h"
#include "../anvil/include/ads/graph.h"

TEST(GraphTest, GetNonexistantVertex) {
	Graph<int>* g = new Graph<int>();
	EXPECT_TRUE(g->Get(5) == NULL);
}
TEST(GraphTest, AddVertex) {
	Graph<int>* g = new Graph<int>();
	EXPECT_TRUE(g->Add(5));
	EXPECT_TRUE(g->Get(5) != NULL);
	EXPECT_FALSE(g->Add(5));
}

TEST(GraphTest, RemoveVertex) {
	Graph<int>* g = new Graph<int>();
	g->Add(5);
	g->Remove(5);
	EXPECT_TRUE(g->Get(5) == NULL);
}