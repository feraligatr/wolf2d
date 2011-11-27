#ifndef _MESSAGE_MANAGER_H_
#define _MESSAGE_MANAGER_H_

#include "Message.h"

class MessageManager
{
public:
	MessageManager();
	virtual ~MessageManager();
	void disposeMessage(Message* message);
	Message* getFreeMessage(MessageHeader header);
};

#endif
