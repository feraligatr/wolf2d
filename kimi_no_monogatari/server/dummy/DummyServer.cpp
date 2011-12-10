#include "pch/pch.h"

#include "Session.h"
#include "msg/MessageParsers.h"

#include "DummyServer.h"

void DummyServer::update()
{
// TODO. move the logic into the needed position.
//{
//	message = got message from queue;
//	handler = factory->gethandler(message);
//	handler->handle(environment);
//	message->dispose();
//}
}

void DummyServer::destroy()
{
	Server::destroy();
}

void DummyServer::dispatchMessage(Session* from, Message* message)
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

	Server::dispatchMessage(from, message);
}

void DummyServer::handleEchoMessage(Session* from, EchoMessageParser* mp)
{
	from->deliver(mp->getMessage());
}
