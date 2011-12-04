#ifndef _TEST_MESSAGE_QUEUE_H_
#define _TEST_MESSAGE_QUEUE_H_

#include "msg/Message.h"

class TestMessageQuque : private boost::noncopyable
{
public:
	void push(Message*);
	Message* pop();

protected:
	typedef std::queue<Message*> MessageMap;
	MessageMap m_messages;
	boost::mutex m_mutex;
};

#endif /* _TEST_MESSAGE_QUEUE_H_ */


