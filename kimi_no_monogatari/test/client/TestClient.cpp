#include "common.h"

#include "TestClient.h"

using boost::asio::ip::tcp;

TestClient::TestClient(boost::asio::io_service& io_service, MessageManager* messageManager)
:m_io_service(io_service)
,m_isConnected(false)
,m_messageManager(messageManager)
{

}

bool TestClient::isConnected() const
{
	return m_isConnected;
}

void TestClient::connect(MessageDispatcher* dispatcher)
{
	m_session.reset(new Session(m_io_service, NULL, dispatcher, m_messageManager));
	tcp::resolver resolver(m_io_service);
	tcp::resolver::query query(tcp::v4(), "127.0.0.1", "92");
	tcp::resolver::iterator iterator = resolver.resolve(query);

	boost::asio::connect(m_session->socket(), iterator);

	m_isConnected = true;
}

void TestClient::sendMessage(Message* message)
{
	m_session->deliver(message);
}

