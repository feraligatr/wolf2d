#ifndef _TEST_GAME_APP_H_
#define _TEST_GAME_APP_H_

#include "ConnectionManager.h"
#include "msg/MessageDispatcher.h"
#include "msg/MessageManager.h"
#include "Client.h"

class TestGameApp : public Client
{
public:
	TestGameApp(ConnectionManager& connectionManager, MessageManager& messageManager, LoggerType* logger);
	virtual ~TestGameApp();
	virtual bool init();
	virtual void update(float interval);

	void handleMessage(Message* message);

	void echo(const char*);

private:
	ConnectionPtr m_connection;
	ConnectionManager& r_connectionManager;
	MessageManager& r_messageManager;
	LoggerType* m_logger;

};

#endif /* _TEST_GAME_APP_H_ */

