#include "pch/pch.h"

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

Message* MessageManager::getFreeMessage(const MessageHeader& header)
{
	Message* m = new Message(this, header.getSize());
	m->setHeader(header);
	return m;
}

Message* MessageManager::getFreeMessage(u32 size)
{
	Message* m = new Message(this, size);
	return m;
}
