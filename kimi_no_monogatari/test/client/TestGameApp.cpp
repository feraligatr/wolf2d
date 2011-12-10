#include "pch/pch.h"

#include "TestGameApp.h"

#include "msg/MessageParsers.h"

TestGameApp::TestGameApp(ConnectionManager* conMgr, MessageManager* msgMgr)
:m_pConMgr(conMgr),
m_msgMgr(msgMgr)
{

}

TestGameApp::~TestGameApp()
{
	m_pConMgr->removeConnection(m_connection);
}

bool TestGameApp::init()
{
	ASSERT(m_connection == NULL);
	m_connection = m_pConMgr->createConnection();
	return m_connection->connect(this);
}

void TestGameApp::update(float interval)
{

}

void TestGameApp::dispatchMessage(Session* from, Message* message)
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
	Message* m = m_msgMgr->getFreeMessage(EchoMessageParser::getRecommendSize());
	EchoMessageParser parser(m);
	parser.setText(content);
	m->setHeader(MessageHeader(MESSAGE_ECHO, EchoMessageParser::getRecommendSize()));
	// log it.
	m_connection->deliver(m);
}
