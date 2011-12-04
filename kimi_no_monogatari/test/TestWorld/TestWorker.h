#ifndef _TEST_WORKER_H_
#define _TEST_WORKER_H_

#include "TestMessageQueue.h"
#include "TestClient.h"
#include "msg/MessageDispatcher.h"
#include "TestGameApp.h"
#include "ConnectionManager.h"

class TestWorker : public MessageDispatcher, public ConnectionManager
	private boost::noncopyable
{
public:
	TestWorker();
	virtual void run();

	void chat(const char* content);
	virtual void dispatchMessage(Session* from, Message* message);

protected:
	void process();

private:
	TestMessageQuque m_queue;
	boost::asio::deadline_timer* m_processTimer;
	MessageManager m_messageManager;

	std::vector<TestGameApp*> m_games;
	TestGameApp* m_controlGame;

};


#endif

