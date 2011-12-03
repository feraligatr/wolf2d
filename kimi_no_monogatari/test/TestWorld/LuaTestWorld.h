#ifndef _LUA_TEST_WORLD_H_
#define _LUA_TEST_WORLD_H_

#include "TestWorld.h"

struct lua_State;

class LuaTestWorld : public TestWorld
{
public:
	LuaTestWorld();
	virtual ~LuaTestWorld();

	// start the world. the world will run in different thread. 
	virtual void start();
	// pause, resume, stop the world, will not implement now.
	virtual void stop();
	virtual void pause();
	virtual void resume();

	virtual void runString(const char* str);

public: // export
	void test();

protected:
	void initLua();
	void registerLibs();
	void registerFunctions();
	void startup();

	lua_State* m_L;
};

#endif
