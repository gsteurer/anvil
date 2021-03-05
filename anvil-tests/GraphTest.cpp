#include "pch.h"
#include "CppUnitTest.h"
#include "../anvil/include/ads/graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil_tests
{
    TEST_CLASS(GraphTest)
    {
    public:

        TEST_METHOD(GetBlankNode)
        {
            Graph<int>* g = new Graph<int>();
            Assert::IsNull(g->Get(5));
        }
        TEST_METHOD(AddNode)
        {
            Graph<int>* g = new Graph<int>();
            g->Add(5);
            Assert::IsNotNull(g->Get(5));
        }
        TEST_METHOD(RemoveNode)
        {
            Graph<int>* g = new Graph<int>();
            g->Add(5);
            g->Remove(5);
            Assert::IsNull(g->Get(5));
        }
    };
}