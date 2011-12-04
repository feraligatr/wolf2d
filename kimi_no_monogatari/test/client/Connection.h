#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "Session.h"
#include "msg/MessageManager.h"
#include "msg/MessageDispatcher.h"
#include "ConnectionManager.h"

class Connection
{
public:
	bool isConnected() const;
	void connect(MessageDispatcher* dispatcher);
	void sendMessage(Message* message);

	void dispose();

	friend class ConnectionManager;
private:
	Connection(boost::asio::io_service& io_service, MessageManager* messageManager, ConnectionManager* connectionManager);
	~Connection();

private:
	boost::asio::io_service& m_io_service;
	MessageManager* m_pMessageManager;
	ConnectionManager* m_pConnectionManager;
	SessionPtr m_session;
	bool m_isConnected;

};


#endif /* _CLIENT_H_ */
