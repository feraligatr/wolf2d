#include "common.h"

#include "TestMessageQueue.h"


void TestMessageQuque::push(Message* msg)
{
	boost::mutex::scoped_lock m_access;
	m_messages.push(msg);
}

Message* TestMessageQuque::pop()
{
	boost::mutex::scoped_lock m_access;
	Message* msg = NULL;
	if (!m_messages.empty())
	{
		msg = m_messages.front();
		m_messages.pop();
	}
	return msg;
}



