#include "common.h"

#include "TestMessageQueue.h"


void TestMessageQuque::push(Message* msg)
{
	boost::mutex::scoped_lock scoped_lock(m_mutex);
	m_messages.push(msg);
}

Message* TestMessageQuque::pop()
{
	boost::mutex::scoped_lock scoped_lock(m_mutex);
	Message* msg = NULL;
	if (!m_messages.empty())
	{
		msg = m_messages.front();
		m_messages.pop();
	}
	return msg;
}



