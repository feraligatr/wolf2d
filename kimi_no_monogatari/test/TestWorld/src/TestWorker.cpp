#include "pch/pch.h"

#include "TestWorker.h"

#define UPDATE_INTERVAL 50

using namespace boost::logging;

TestWorker::TestWorker()
:m_numGames(1)
{
	initLogger();
}

void TestWorker::initLogger()
{
	m_consoleLogger.writer().add_formatter( formatter::idx() );
	m_consoleLogger.writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
	m_consoleLogger.writer().add_formatter( formatter::append_newline() );

	//        ... and where should it be written to
	m_consoleLogger.writer().add_destination( destination::dbg_window() );
	m_consoleLogger.turn_cache_off();

	m_fileLogger.writer().add_formatter( formatter::idx() );
	m_fileLogger.writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
	m_fileLogger.writer().add_formatter( formatter::append_newline() );

	//        ... and where should it be written to
	m_fileLogger.writer().add_destination( destination::file("out.txt") );
	m_fileLogger.turn_cache_off();
}

void TestWorker::removeConnection(ConnectionPtr con)
{
	con->stopAll();
	m_connections.erase(con);
}

ConnectionPtr TestWorker::createConnection()
{
	ConnectionPtr con(new Connection(m_io_service, m_messageManager, *this));
	m_connections.insert(con);
	return con;
}

void TestWorker::run()
{
	ASSERT(m_numGames > 0);
	for (u32 i = 0; i < m_numGames; i++)
	{
		GameAppPtr app;
		if (i == 0)
		{
			app.reset(new TestGameApp(*this, m_messageManager, &m_consoleLogger));
		}
		else
		{
			app.reset(new TestGameApp(*this, m_messageManager, &m_fileLogger));
		}
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
