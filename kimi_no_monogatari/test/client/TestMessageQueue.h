#ifndef _TEST_MESSAGE_QUEUE_H_
#define _TEST_MESSAGE_QUEUE_H_

#include <queue>
#include "Message.h"

#include <boost/thread.hpp>

class TestMessageQuque
{
public:
	void push(Message*);
	Message* pop();

protected:
	typedef std::queue<Message*> MessageMap;
	MessageMap m_messages;
	boost::mutex m_access;
};

#endif /* _TEST_MESSAGE_QUEUE_H_ */


