#ifndef _TEST_WORKER_H_
#define _TEST_WORKER_H_

#include <boost/thread.hpp>

#include "TestMessageQueue.h"
#include "TestClient.h"
#include "MessageDispatcher.h"

class TestWorker : public MessageDispatcher
{
public:
	TestWorker();
	void operator()();

	void chat(const char* content);
	virtual void dispatchMessage(Session* from, Message* message);

protected:
	void process();

private:
	TestMessageQuque m_queue;
	boost::asio::deadline_timer* m_processTimer;
	MessageManager m_messageManager;
	TestClient* m_client;
};


#endif

