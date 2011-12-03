#include "common.h"

#include "SessionManager.h"

void SessionManager::start(SessionPtr session)
{
	m_sessions.insert(session);
	session->start();
}

void SessionManager::stop(SessionPtr session)
{
	m_sessions.erase(session);
	session->stop();
}

void SessionManager::stopAll()
{
	std::for_each(m_sessions.begin(), m_sessions.end(),
		boost::bind(&Session::stop, _1));
	m_sessions.clear();
}