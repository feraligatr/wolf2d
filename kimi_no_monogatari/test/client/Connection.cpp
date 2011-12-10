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

bool Connection::connect(MessageDispatcher* dispatcher)
{
	try
	{
		m_session.reset(new Session(m_io_service, NULL, dispatcher, m_pMessageManager));
		tcp::resolver resolver(m_io_service);
		tcp::resolver::query query(tcp::v4(), "127.0.0.1", "92");
		tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::connect(m_session->socket(), iterator);
		m_session->start();
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
		std::cerr << "TestWorker terminate" << "\n";
		return false;
	}
	m_isConnected = true;
	return true;
}

void Connection::stop()
{
	m_session->stop();
}

void Connection::deliver(Message* message)
{
	m_session->deliver(message);
}

void Connection::dispose()
{
	ASSERT(m_pConnectionManager);
	m_pConnectionManager->removeConnection(shared_from_this());
}
