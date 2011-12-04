#ifndef _CONNECTION_MANAGER_H_
#define _CONNECTION_MANAGER_H_

#include "Connection.h"

class ConnectionManager
{
public:
	void removeConnection(Connection* con);
	Connection* createConnection();

private:

};


#endif /* _CONNECTION_MANAGER_H_ */