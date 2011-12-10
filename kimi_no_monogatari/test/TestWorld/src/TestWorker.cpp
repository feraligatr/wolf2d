#include "pch/pch.h"

#include "TestWorker.h"

#define UPDATE_INTERVAL 50

TestWorker::TestWorker()
:m_numGames(1)
{

}

void TestWorker::removeConnection(ConnectionPtr con)
{
	con->stop();
	m_connections.erase(con);
}

ConnectionPtr TestWorker::createConnection()
{
	ConnectionPtr con;
	con.reset(new Connection(m_io_service, &m_messageManager, this));
	m_connections.insert(con);
	return con;
}

void TestWorker::run()
{
	for (u32 i = 0; i < m_numGames; i++)
	{
		GameAppPtr app;
		app.reset(new TestGameApp(this, &m_messageManager));
		if (app->init())
		{
			m_games.push_back(app);
		}
	}
	if (m_games.empty())
	{
		return;
	}
	m_controlGame = m_games.at(0);

	m_processTimer.reset(new boost::asio::deadline_timer(m_io_service));
	m_processTimer->expires_from_now(boost::posix_time::milliseconds(UPDATE_INTERVAL));
	m_processTimer->async_wait(boost::bind(&TestWorker::process, this));
	m_io_service.run();
}

void TestWorker::process()
{
	for (std::vector<GameAppPtr>::iterator iter = m_games.begin(); iter != m_games.end(); ++iter)
	{
		(*iter)->update((float)UPDATE_INTERVAL / 1000);
	}
	m_processTimer->expires_from_now(boost::posix_time::milliseconds(UPDATE_INTERVAL));
	m_processTimer->async_wait(boost::bind(&TestWorker::process, this));
}

void TestWorker::echo(const char* content)
{
	if (m_controlGame)
	{
		m_controlGame->echo(content);
	}
}
