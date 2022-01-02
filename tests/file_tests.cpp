#include "anvil/file/mesh.h"
#include "anvil/file/wavefront.h"
#include "gtest/gtest.h"

TEST(FileTests, Ctor) {
    anvil::file::Mesh test;

    EXPECT_EQ(static_cast<isize_t>(0), test.verts.Length());
}
