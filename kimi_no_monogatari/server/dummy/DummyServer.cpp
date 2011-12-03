#include "server_pch.h"

#include "DummyServer.h"
#include "Session.h"

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
	Server::dispatchMessage(from, message);
}
