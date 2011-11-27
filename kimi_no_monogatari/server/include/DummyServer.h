#ifndef _DUMMY_SERVER_H_
#define _DUMMY_SERVER_H_

#include "Server.h"

#include "SessionManager.h"
#include "MessageManager.h"
#include "DummyMessageDispatcher.h"

class DummyServer : public Server
{
public:
	virtual void update();
	virtual SessionManager* getSessionManager();
	virtual void destroy();
	virtual Session* getNewSession(boost::asio::io_service& io_service);

private:
	SessionManager m_sessionManager;
	MessageManager m_messageManager;
	DummyMessageDispatcher m_dispatcher;

};



#endif /* _DUMMY_SERVER_H_ */
