#ifndef _MESSAGE_DISPATCHER_H_
#define _MESSAGE_DISPATCHER_H_

#include "Message.h"

class MessageDispatcher
{
public:
	virtual ~MessageDispatcher() {}
	virtual void dispatchMessage(Message* message) = 0;
};


#endif
