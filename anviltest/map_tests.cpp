#include "ads/map.h"
#include "gtest/gtest.h"
#include "option.h"

TEST(MapTests, Ctor) {
    Map<int, int> test;
    test.Insert(5, 10);
    Hash(5);
}