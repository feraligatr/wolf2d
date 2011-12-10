#ifndef _TEST_GAME_APP_H_
#define _TEST_GAME_APP_H_

#include "ConnectionManager.h"
#include "msg/MessageDispatcher.h"
#include "msg/MessageManager.h"
#include "Client.h"

class TestGameApp : public Client, MessageDispatcher
{
public:
	TestGameApp(ConnectionManager* conMgr, MessageManager* msgMgr);
	virtual ~TestGameApp();
	virtual bool init();
	virtual void update(float interval);

	virtual void dispatchMessage(Session* from, Message* message);

	void echo(const char*);

private:
	ConnectionPtr m_connection;
	ConnectionManager* m_pConMgr;
	MessageManager* m_msgMgr;

};

#endif /* _TEST_GAME_APP_H_ */

