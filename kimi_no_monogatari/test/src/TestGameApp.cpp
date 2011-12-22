#include "pch/pch.h"

#include "TestGameApp.h"

#include "msg/MessageParsers.h"
#include "Logger.h"

TestGameApp::TestGameApp(ConnectionManager& connectionManager, MessageManager& messageManager, LoggerType* logger)
:Client(NULL),
r_connectionManager(connectionManager),
r_messageManager(messageManager),
m_logger(logger)
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
	m_connection->setMessageHandler(boost::bind(&TestGameApp::handleMessage, this, _1));
	return m_connection->connect();
}

void TestGameApp::update(float interval)
{

}

void TestGameApp::handleMessage(Message* message)
{
	ASSERT(message);
	switch(message->getType())
	{
	case MESSAGE_ECHO:
		{
			EchoMessageParser parser(message);
			LAPP_L_(m_logger) << " receiving message echo: " << parser.getText();
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
		LAPP_L_(m_logger) << "Echoing but Connection invalid." ;
		return;
	}
	Message* m = r_messageManager.getFreeMessage(EchoMessageParser::getRecommendSize());
	EchoMessageParser parser(m);
	parser.setText(content);
	m->setHeader(MessageHeader(MESSAGE_ECHO, EchoMessageParser::getRecommendSize()));
	LAPP_L_(m_logger) << "echo " << content;
	m_connection->deliver(m);
}
