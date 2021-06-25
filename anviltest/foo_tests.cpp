#include "foo.h"
#include "gtest/gtest.h"

TEST(FooTests, Ctor) {
    Foo<int>* foo = new Foo<int>();
    EXPECT_EQ(-1, *foo->m_id);
    delete foo;

    foo = new Foo<int>(5);
    EXPECT_EQ(5, *foo->m_id);
    delete foo;
}

TEST(FooTests, GetID) {
    Foo<int>* foo = new Foo<int>(5);
    EXPECT_EQ(5, foo->ID());
    delete foo;
}

TEST(FooTests, RefCopy) {
    Foo<int>* foo = new Foo<int>();
    Foo<int>* foo_copy = new Foo<int>(&*foo);
    EXPECT_NE(foo, foo_copy);
    EXPECT_NE(foo->m_id, foo_copy->m_id);
    EXPECT_EQ(*foo->m_id, *foo_copy->m_id);
    delete foo;
    delete foo_copy;
}

TEST(FooTests, PtrCopy) {
    Foo<int>* foo = new Foo<int>();
    Foo<int>* foo_copy = new Foo<int>(foo);
    EXPECT_NE(foo, foo_copy);
    EXPECT_NE(foo->m_id, foo_copy->m_id);
    EXPECT_EQ(*foo->m_id, *foo_copy->m_id);
    delete foo;
    delete foo_copy;
}

TEST(FooTests, CopyAssign) {
    Foo<int> a(5);
    Foo<int> b = a;
    Foo<int> c;

    EXPECT_NE(a.m_id, b.m_id);
    EXPECT_EQ(a.ID(), b.ID());

    *a.m_id = 7;
    c = a;
    EXPECT_NE(a.m_id, c.m_id);
    EXPECT_EQ(a.ID(), c.ID());

    *a.m_id = 9;
    a = b = c;
    EXPECT_EQ(a.ID(), c.ID());
    EXPECT_EQ(a.ID(), c.ID());
    EXPECT_EQ(a.ID(), c.ID());
}

TEST(FooTests, EQ) {
    Foo<int>* lhs = new Foo<int>(5);
    Foo<int>* rhs = new Foo<int>(5);

    EXPECT_TRUE(*lhs == *rhs);
    EXPECT_EQ(*lhs, *rhs);
    *rhs->m_id = 6;
    EXPECT_FALSE(*lhs == *rhs);
    delete lhs;
    delete rhs;
}
