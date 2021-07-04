#include <stdio.h>

#include "anvil/option.h"
#include "anvil/smartpointer.h"
#include "foo.h"
#include "gtest/gtest.h"
TEST(SmartPointerTests, AutoPointerMove) {
    anvil::internal::AutoPointer<Foo<int>> test(new Foo<int>(69));
    anvil::internal::AutoPointer<Foo<int>> move(test);
    int x{5};
    int& lref{x};
    int&& rref{5};

    printf("%d %c\n", lref, rref);
}