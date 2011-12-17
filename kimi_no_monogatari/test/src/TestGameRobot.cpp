#include "pch/pch.h"
#include "TestGameRobot.h"

TestGameRobot::TestGameRobot(ConnectionManager& connectionManager, MessageManager& messageManager, LoggerType* logger, const std::string& name)
:TestGameApp(connectionManager, messageManager, logger)
,m_echoTimer(m_gen)
,m_name(name)
,m_count(0)
{
	// hack to have different seed for m_gen.
	m_gen.seed(random::roll_die(random::g_rndGen, 100000));
}

bool TestGameRobot::init()
{
	m_echoTimer.start(0.5f, 5.0f);
	return TestGameApp::init();
}

void TestGameRobot::update(float interval)
{
	m_echoTimer.update(interval);
	if (m_echoTimer.isTimeout())
	{
		char buffer[128];
		sprintf(buffer, "%s: echo something: %d times ", m_name.c_str(), m_count);
		echo(buffer);
		m_count++;
		m_echoTimer.restart();
	}
}

