#ifndef _TEST_WORLD_H
#define _TEST_WORLD_H

class TestWorld
{
public:
	virtual ~TestWorld() {}

	
	virtual void start() = 0;


	virtual void stop() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void runString(const char* str) = 0;

};


#endif /* _TEST_WORLD_H */

