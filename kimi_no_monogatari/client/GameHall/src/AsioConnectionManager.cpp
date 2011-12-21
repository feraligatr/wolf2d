#include "pch/pch.h"

#include "AsioConnectionManager.h"

AsioConnectionManager::AsioConnectionManager()
{
	m_messageManager = new MessageManager();
}

AsioConnectionManager::~AsioConnectionManager()
{
	for (ConnectionList::iterator iter = m_connections.begin(); iter != m_connections.end(); ++iter)
	{
		(*iter)->stopAll();
	}
	delete m_messageManager;
}

void AsioConnectionManager::removeConnection(ConnectionPtr con)
{
	con->stopAll();
	m_connections.erase(con);
}

ConnectionPtr AsioConnectionManager::createConnection()
{
	ConnectionPtr con(new Connection(m_io_service, *m_messageManager, *this));
	m_connections.insert(con);
	return con;
}

void AsioConnectionManager::update()
{
	m_io_service.poll();
}
