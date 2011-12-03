#ifndef _SERVER_H_
#define _SERVER_H_

#include "MessageDispatcher.h"

class Session;
class SessionManager;
class MessageManager;

class Server : public MessageDispatcher
{
public:
	Session* getNewSession(boost::asio::io_service& io_service);
	SessionManager* getSessionManager();

	// update everything every interval time.
	// TODO: add float inerval as update parameter. ? or get interval from other place?
	virtual void update() = 0;
	virtual void destroy();

	virtual void dispatchMessage(Session* from, Message* message);

protected:
	Server();
	virtual ~Server();

	SessionManager* m_pSessionManager;
	MessageManager* m_pMessageManager;
};

#endif /* _SERVER_H_ */
