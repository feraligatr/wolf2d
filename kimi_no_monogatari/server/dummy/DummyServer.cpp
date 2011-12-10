#include "pch/pch.h"

#include "Session.h"
#include "msg/MessageParsers.h"

#include "DummyServer.h"

void DummyServer::update()
{

}

void DummyServer::dispatchMessage(SessionPtr from, Message* message)
{
	switch (message->getType())
	{
	case MESSAGE_ECHO:
		{
			EchoMessageParser mp(message);
			handleEchoMessage(from, &mp);
		}
		break;
	default:
		printf("Invalid message %x.\n", message->getType());
	}
}

void DummyServer::handleEchoMessage(SessionPtr from, EchoMessageParser* mp)
{
	from->deliver(mp->getMessage());
}
