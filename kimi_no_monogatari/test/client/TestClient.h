#ifndef _TEST_CLIENT_H_
#define _TEST_CLIENT_H_

#include "Session.h"
#include "msg/MessageManager.h"
#include "msg/MessageDispatcher.h"

class TestClient
{
public:
	TestClient(boost::asio::io_service& io_service, MessageManager* messageManager);

	bool isConnected() const;
	void connect(MessageDispatcher* dispatcher);
	void sendMessage(Message* message);

private:
	boost::asio::io_service& m_io_service;
	MessageManager* m_messageManager;
	SessionPtr m_session;
	bool m_isConnected;

};


#endif /* _TEST_SERVER_H_ */
