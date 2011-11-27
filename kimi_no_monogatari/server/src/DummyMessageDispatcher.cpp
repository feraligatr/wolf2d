#include "server_pch.h"

#include "DummyMessageDispatcher.h"


void DummyMessageDispatcher::dispatchMessage(Message* message)
{
	// TODO. message dispatch to needed position.
	message->dispose();
}
