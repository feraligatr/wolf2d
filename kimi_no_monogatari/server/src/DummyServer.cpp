#include "server_pch.h"

#include "DummyServer.h"
#include "Session.h"

Server* Server::getInstance()
{
	if (!m_instance)
	{
		m_instance = new DummyServer();
	}
	return m_instance;
}

void DummyServer::update()
{
// TODO. move the logic into the needed position.
//{
//	message = got message from queue;
//	handler = factory->gethandler(message);
//	handler->handle(environment);
//	message->dispose();
//}
}

SessionManager* DummyServer::getSessionManager()
{
	return &m_sessionManager;
}

Session* DummyServer::getNewSession(boost::asio::io_service& io_service)
{
	return new Session(io_service, m_sessionManager, m_dispatcher, m_messageManager);
}

void DummyServer::destroy()
{
	m_sessionManager.stopAll();
}
