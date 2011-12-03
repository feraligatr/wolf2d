#ifndef _TEST_WORKER_H_
#define _TEST_WORKER_H_

#include <boost/thread.hpp>

#include "TestMessageQueue.h"

class TestWorker
{
public:
	TestWorker();
	void operator()();

	void chat(const char* content);

private:
	bool m_connected;
	TestClient m_client;

};


#endif

