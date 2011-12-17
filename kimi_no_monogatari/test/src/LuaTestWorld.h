#ifndef _LUA_TEST_WORLD_H_
#define _LUA_TEST_WORLD_H_

#include "TestWorld.h"

#include "TestWorker.h"

class LuaTestWorld : public TestWorld,
	private boost::noncopyable
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
	// for the only manual game.
	void echo(const char* content);

protected:
	void initLua();
	void registerLibs();
	void registerFunctions();
	void startup();

	lua_State* m_L;

	boost::thread m_mainWorkerThread;
	TestWorker m_mainWorker;

	std::vector<TestWorker*> m_otherWorkers;

};

#endif
