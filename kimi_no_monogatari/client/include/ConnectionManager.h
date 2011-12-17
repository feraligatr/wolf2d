#ifndef _CONNECTION_MANAGER_H_
#define _CONNECTION_MANAGER_H_

#include "Connection.h"

class ConnectionManager
{
public:
	virtual void removeConnection(ConnectionPtr con) = 0;
	virtual ConnectionPtr createConnection() = 0;
};


#endif /* _CONNECTION_MANAGER_H_ */