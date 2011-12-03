#include "include/common.h"

#include "msg/Message.h"
#include "MessageManager.h"

Message::Message(MessageManager* manager, u32 capacity)
:m_manager(manager), m_buffer(NULL), m_capacity(capacity)
{
	ASSERT(capacity > 0);
	m_buffer = new u8[capacity + sizeof(MessageHeader)];
}

Message::~Message()
{
	delete[] m_buffer;
}

void Message::dispose()
{
	ASSERT(m_manager);
	m_manager->disposeMessage(this);
}

void Message::setMessageHeader(const MessageHeader& header) 
{
	memcpy(m_buffer, &header, sizeof(MessageHeader));
}
