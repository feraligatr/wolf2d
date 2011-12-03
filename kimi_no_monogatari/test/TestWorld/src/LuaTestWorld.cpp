#include "common.h"

#include "LuaTestWorld.h"
#include <iostream>
extern "C"
{
 #include <lualib.h>
}
#include <luabind/luabind.hpp>

using namespace luabind;

LuaTestWorld::LuaTestWorld()
:m_L(NULL)
{

}

LuaTestWorld::~LuaTestWorld()
{
	stop();
}

void LuaTestWorld::stop()
{
	if (m_L)
	{
		lua_close(m_L);
	}
}

void LuaTestWorld::pause()
{

}

void LuaTestWorld::resume()
{

}

void LuaTestWorld::initLua()
{
	m_L = lua_open();
}

void LuaTestWorld::runString(const char* str)
{
	if (luaL_dostring(m_L, str) != 0)
	{
		std::cout << lua_tostring(m_L, -1);
		lua_pop(m_L, 2);
		std::cout << std::endl;
	}
}

void LuaTestWorld::start()
{
	initLua();
	registerLibs();
	registerFunctions();
	startup();
}

void LuaTestWorld::registerLibs()
{
	luaL_openlibs(m_L);
}

void LuaTestWorld::registerFunctions()
{
	luabind::open(m_L);

	module(m_L)
	[
		class_<LuaTestWorld>("LuaTestWorld")
			.def("test", &LuaTestWorld::test)
	];
}

void LuaTestWorld::startup()
{
	luabind::globals(m_L)["world"] = this;
}

void LuaTestWorld::test()
{
	std::cout << "Hello World!" << std::endl;
}
