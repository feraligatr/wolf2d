#ifndef _DUMMY_SERVER_H_
#define _DUMMY_SERVER_H_

#include "Server.h"

class EchoMessageParser;

class DummyServer : public Server
{
public:
	virtual void update();
	virtual void destroy();
	virtual void dispatchMessage(Session* from, Message* message);
private:
	void handleEchoMessage(Session* from, EchoMessageParser* mp);
};



#endif /* _DUMMY_SERVER_H_ */
