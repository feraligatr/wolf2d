#include "pch/pch.h"

#include "TestWorker.h"
#include "TestClient.h"


TestWorker::TestWorker()
:m_processTimer(NULL)
{

}

void TestWorker::run()
{
	boost::asio::io_service io_service;
	m_client = new TestClient(io_service, &m_messageManager);
	if (!m_client->isConnected())
	{
		try
		{
			m_client->connect(this);
		}
		catch (std::exception& e)
		{
			delete m_client;
			std::cerr << "Exception: " << e.what() << "\n";
			std::cerr << "TestWorker terminate" << "\n";
			return;
		}
	}
	m_processTimer = new boost::asio::deadline_timer(io_service);
	m_processTimer->expires_from_now(boost::posix_time::milliseconds(50));
	m_processTimer->async_wait(boost::bind(&TestWorker::process, this));
	io_service.run();

	delete m_client;
	delete m_processTimer;
}

void TestWorker::process()
{
	Message* message = NULL;
	while(message = m_queue.pop())
	{
		m_client->sendMessage(message);
		message->dispose();
	}
	m_processTimer->expires_from_now(boost::posix_time::milliseconds(50));
}

void TestWorker::chat(const char* content)
{
//	Message* message = m_messageManager->getFreeMessage(chat_message, 1024);
//	// package message by content.
//	m_queue.push(message);
}

void TestWorker::dispatchMessage(Session* from, Message* message)
{
	// handle the message.
	message->dispose();
}

