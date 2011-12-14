#ifndef _TEST_GAME_ROBOT_H_
#define _TEST_GAME_ROBOT_H_

#include "TestGameApp.h"
#include "RandomUtil.h"

class TestGameRobot : public TestGameApp
{
public:
	TestGameRobot(ConnectionManager& connectionManager, MessageManager& messageManager, LoggerType* logger, const std::string& name);

	virtual bool init();
	virtual void update(float interval);

private:
	random::RndGen m_gen;
	RandomTimer m_echoTimer;
	std::string m_name;
	u32 m_count;
};


#endif /* _TEST_GAME_ROBOT_H_ */
