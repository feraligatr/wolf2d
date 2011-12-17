#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "msg/MessageManager.h"
#include "msg/MessageDispatcher.h"
#include "SessionManager.h"

class ConnectionManager;

class Connection : public SessionManager, public boost::enable_shared_from_this<Connection>,
	private boost::noncopyable
{
public:
	bool isConnected() const;
	bool connect(MessageDispatcher& dispatcher);
	void deliver(Message* message);

	void dispose();

	Connection(boost::asio::io_service& io_service, MessageManager& messageManager, ConnectionManager& connectionManager);

	virtual void start(SessionPtr session);
	virtual void stop(SessionPtr session);
	virtual void stopAll();

private:
	boost::asio::io_service& m_io_service;
	MessageManager& r_messageManager;
	ConnectionManager& r_connectionManager;
	bool m_isConnected;
	SessionPtr m_session;
};


#endif /* _CONNECTION_H_ */
