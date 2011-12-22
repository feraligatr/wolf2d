#ifndef _SIMPLE_CLIENT_H_
#define _SIMPLE_CLIENT_H_

#include "Client.h"

class ConnectionManager;

class SimpleClient : public Client
{
public:
	SimpleClient(RenderContext* renderContext, ConnectionManager& connectionManager);
	virtual ~SimpleClient();
	virtual void update(float);
	virtual bool init();

protected:
	ConnectionManager& r_connectionManager;

};

#endif /* _SIMPLE_CLIENT_H_ */
