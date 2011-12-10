#ifndef _SERVER_H_
#define _SERVER_H_

#include "msg/MessageDispatcher.h"

class SessionManager;
class MessageManager;

class Server : public MessageDispatcher
{
public:
	SessionPtr getNewSession(boost::asio::io_service& io_service);

	// update everything every interval time.
	// TODO: add float inerval as update parameter. ? or get interval from other place?
	virtual void update() = 0;
	virtual void destroy();

	virtual void dispatchMessage(SessionPtr from, Message* message) = 0;

	virtual void startSession(SessionPtr session);

protected:
	Server();
	virtual ~Server();

	SessionManager* m_sessionManager;
	MessageManager* m_messageManager;
};

#endif /* _SERVER_H_ */
