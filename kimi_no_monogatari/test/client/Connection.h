#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "Session.h"
#include "msg/MessageManager.h"
#include "msg/MessageDispatcher.h"

class ConnectionManager;

class Connection : public boost::enable_shared_from_this<Connection>,
	private boost::noncopyable
{
public:
	bool isConnected() const;
	bool connect(MessageDispatcher* dispatcher);
	void stop();
	void deliver(Message* message);

	void dispose();

	Connection(boost::asio::io_service& io_service, MessageManager* messageManager, ConnectionManager* connectionManager);

private:
	boost::asio::io_service& m_io_service;
	MessageManager* m_pMessageManager;
	ConnectionManager* m_pConnectionManager;
	SessionPtr m_session;
	bool m_isConnected;
};

typedef boost::shared_ptr<Connection> ConnectionPtr;


#endif /* _CONNECTION_H_ */
