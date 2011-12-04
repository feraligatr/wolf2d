#include "pch/pch.h"

#include "Connection.h"
#include "ConnectionManager.h"

using boost::asio::ip::tcp;

Connection::Connection(boost::asio::io_service& io_service, MessageManager* messageManager, ConnectionManager* connectionManager)
:m_io_service(io_service)
,m_isConnected(false)
,m_pMessageManager(messageManager)
,m_pConnectionManager(connectionManager)
{

}

bool Connection::isConnected() const
{
	return m_isConnected;
}

void Connection::connect(MessageDispatcher* dispatcher)
{
	try
	{
		m_session.reset(new Session(m_io_service, NULL, dispatcher, m_pMessageManager));
		tcp::resolver resolver(m_io_service);
		tcp::resolver::query query(tcp::v4(), "127.0.0.1", "92");
		tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::connect(m_session->socket(), iterator);
	}
	catch(std::exception&)
	{
		return;
	}
	m_isConnected = true;
}

void Connection::sendMessage(Message* message)
{
	m_session->deliver(message);
}

void Connection::dispose()
{
	ASSERT(m_pConnectionManager);
	m_pConnectionManager->removeConnection(this);
}
