#include "pch/pch.h"

#include "Session.h"
#include "msg/MessageParsers.h"
#include "SessionManager.h"

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
		{
			LERR_ << "Invalid message " << message->getType();
			m_sessionManager->stop(from);
		}
	}
}

void DummyServer::handleEchoMessage(SessionPtr from, EchoMessageParser* mp)
{
	from->deliver(mp->getMessage());
}
