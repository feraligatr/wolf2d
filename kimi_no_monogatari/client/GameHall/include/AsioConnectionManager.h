#ifndef _ASIO_CONNECTION_MANAGER_H_
#define _ASIO_CONNECTION_MANAGER_H_

#include "ConnectionManager.h"
#include "msg/MessageManager.h"

class AsioConnectionManager : public ConnectionManager
{
public:
	AsioConnectionManager();
	virtual ~AsioConnectionManager();
	
	virtual void removeConnection(ConnectionPtr con);
	virtual ConnectionPtr createConnection();

	void update();
private:
	typedef std::set<ConnectionPtr> ConnectionList;
	ConnectionList m_connections;
	MessageManager* m_messageManager;
	boost::asio::io_service m_io_service;
};

#endif _ASIO_CONNECTION_MANAGER_H_
