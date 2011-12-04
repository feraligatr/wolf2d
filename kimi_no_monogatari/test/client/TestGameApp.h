#ifndef _TEST_GAME_APP_H_
#define _TEST_GAME_APP_H_

#include "ConnectionManager.h"

class TestGameApp
{
public:
	TestGameApp();
	virtual ~TestGameApp();
	virtual void init();
	virtual void update(float interval);


};

#endif /* _TEST_GAME_APP_H_ */

