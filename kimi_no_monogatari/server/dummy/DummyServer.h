#ifndef _DUMMY_SERVER_H_
#define _DUMMY_SERVER_H_

#include "Server.h"

class DummyServer : public Server
{
public:
	virtual void update();
	virtual void destroy();
	virtual void dispatchMessage(Session* from, Message* message);
};



#endif /* _DUMMY_SERVER_H_ */
