#include "pch/pch.h"

#include "Connection.h"
#include "ConnectionManager.h"

using boost::asio::ip::tcp;

Connection::Connection(boost::asio::io_service& io_service, MessageManager& messageManager, ConnectionManager& connectionManager)
:m_io_service(io_service)
,m_isConnected(false)
,r_messageManager(messageManager)
,r_connectionManager(connectionManager)
{

}

bool Connection::isConnected() const
{
	return m_isConnected;
}

bool Connection::connect()
{
	try
	{
		SessionPtr session(new Session(m_io_service, *this, *this, r_messageManager));
		tcp::resolver resolver(m_io_service);
		tcp::resolver::query query(tcp::v4(), "127.0.0.1", "92");
		tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::connect(session->socket(), iterator);
		m_session = session;
		start(session);
	}
	catch(std::exception& e)
	{
		LERR_ << "Exception: " << e.what();
		LERR_ << "TestWorker terminate";
		return false;
	}
	m_isConnected = true;
	return true;
}

void Connection::dispatchMessage(SessionPtr from, Message* message)
{
	m_messageHandler(message);
}

void Connection::deliver(Message* message)
{
	m_session->deliver(message);
}

void Connection::dispose()
{
	r_connectionManager.removeConnection(shared_from_this());
}

void Connection::start(SessionPtr session)
{
	ASSERT(session == session);
	SessionManager::start(session);
}

void Connection::stop(SessionPtr session)
{
	ASSERT(session == session);
	SessionManager::stop(session);
}

void Connection::stopAll()
{
	m_session.swap(SessionPtr());
	SessionManager::stopAll();
}
