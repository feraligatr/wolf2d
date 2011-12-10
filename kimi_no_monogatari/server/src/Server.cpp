#include "pch/pch.h"

#include "Server.h"
#include "SessionManager.h"
#include "msg/MessageManager.h"
#include "Session.h"

Server::Server()
{
	m_sessionManager = new SessionManager();
	m_messageManager = new MessageManager();
}

void Server::destroy()
{
	m_sessionManager->stopAll();
}

Server::~Server()
{
	delete m_messageManager;
	delete m_sessionManager;
}

SessionPtr Server::getNewSession(boost::asio::io_service& io_service)
{
	return SessionPtr(new Session(io_service, *m_sessionManager, *this, *m_messageManager));
}

void Server::startSession(SessionPtr session)
{
	m_sessionManager->start(session);
}
