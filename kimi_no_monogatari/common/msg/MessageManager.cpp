#include "common.h"

#include "msg/MessageManager.h"


MessageManager::MessageManager()
{

}

MessageManager::~MessageManager()
{

}

void MessageManager::disposeMessage(Message* message)
{
	delete message;
}

Message* MessageManager::getFreeMessage(MessageHeader header)
{
	Message* m = new Message(this, header.getSize());
	m->setMessageHeader(header);
	return m;
}

