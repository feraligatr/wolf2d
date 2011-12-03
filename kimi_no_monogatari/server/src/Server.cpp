#include "server_pch.h"

#include "Server.h"
#include "SessionManager.h"
#include "MessageManager.h"

Server::Server()
{
	m_pSessionManager = new SessionManager();
	m_pMessageManager = new MessageManager();
}

void Server::dispatchMessage(Session* from, Message* message)
{
	message->dispose();
}

void Server::destroy()
{
	m_pSessionManager->stopAll();
}

Server::~Server()
{
	delete m_pMessageManager;
	delete m_pSessionManager;
}

SessionManager* Server::getSessionManager()
{
	return m_pSessionManager;
}

Session* Server::getNewSession(boost::asio::io_service& io_service)
{
	return new Session(io_service, m_pSessionManager, this, m_pMessageManager);
}
