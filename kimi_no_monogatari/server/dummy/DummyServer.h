#ifndef _DUMMY_SERVER_H_
#define _DUMMY_SERVER_H_

#include "Server.h"

class EchoMessageParser;

class DummyServer : public Server
{
public:
	virtual void update();
	virtual void dispatchMessage(SessionPtr from, Message* message);
private:
	void handleEchoMessage(SessionPtr from, EchoMessageParser* mp);
};



#endif /* _DUMMY_SERVER_H_ */
