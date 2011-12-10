#include "pch/pch.h"

#include "TestGameApp.h"

#include "msg/MessageParsers.h"

TestGameApp::TestGameApp(ConnectionManager& connectionManager, MessageManager& messageManager)
:r_connectionManager(connectionManager),
r_messageManager(messageManager)
{

}

TestGameApp::~TestGameApp()
{
	r_connectionManager.removeConnection(m_connection);
}

bool TestGameApp::init()
{
	ASSERT(m_connection == NULL);
	m_connection = r_connectionManager.createConnection();
	return m_connection->connect(*this);
}

void TestGameApp::update(float interval)
{

}

void TestGameApp::dispatchMessage(SessionPtr from, Message* message)
{
	ASSERT(message);
	switch(message->getType())
	{
	case MESSAGE_ECHO:
		{
			EchoMessageParser parser(message);
			// log it.
		}
		break;
	default:
		break;
	}

	message->dispose();
}

void TestGameApp::echo(const char* content)
{
	ASSERT(m_connection);
	if (!m_connection->isConnected())
	{
		// log it.
		return;
	}
	Message* m = r_messageManager.getFreeMessage(EchoMessageParser::getRecommendSize());
	EchoMessageParser parser(m);
	parser.setText(content);
	m->setHeader(MessageHeader(MESSAGE_ECHO, EchoMessageParser::getRecommendSize()));
	// log it.
	m_connection->deliver(m);
}
