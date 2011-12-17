#ifndef _TEST_WORKER_H_
#define _TEST_WORKER_H_

#include "TestGameApp.h"
#include "ConnectionManager.h"

class TestWorker : public ConnectionManager,
	private boost::noncopyable
{
public:
	TestWorker();
	virtual void run();

	virtual void removeConnection(ConnectionPtr con);
	virtual ConnectionPtr createConnection();

	void echo(const char* content);

protected:
	void process();

	void initLogger();

private:
	boost::shared_ptr<boost::asio::deadline_timer> m_processTimer;
	MessageManager m_messageManager;

	typedef boost::shared_ptr<TestGameApp> GameAppPtr;

	std::vector<GameAppPtr> m_games;
	GameAppPtr m_controlGame;

	u32 m_numGames;
	boost::asio::io_service m_io_service;

	std::set<ConnectionPtr> m_connections;

	LoggerType m_consoleLogger;
	LoggerType m_fileLogger;
};


#endif

