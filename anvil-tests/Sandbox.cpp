#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../lua/lua/lua.h"
#include "../lua/lua/lualib.h"
#include "../lua/lua/lauxlib.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil_tests
{
    TEST_CLASS(Sandbox)
    {
    public:

        TEST_METHOD(Tests)
        {
            lua_State* state = luaL_newstate();
            lua_close(state);
        }
    };
}