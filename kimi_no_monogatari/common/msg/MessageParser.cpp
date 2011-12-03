#include "common.h"

#include "msg/Message.h"
#include "msg/MessageParser.h"

MessageParser::MessageParser(Message* message)
:m_pMessage(message)
{
}

MessageParser::~MessageParser()
{
}

void MessageParser::setData(u32 pos, void* data, u32 len)
{
	ASSERT(len > 0 && data);
	ASSERT(m_pMessage && m_pMessage->getBodySize() >= pos + len && m_pMessage->getBody());

	u8* msgBody = m_pMessage->getBody();
	memcpy(msgBody + pos, data, len);
}

void* MessageParser::getData(u32 pos)
{
	ASSERT(m_pMessage && m_pMessage->getBodySize() > pos && m_pMessage->getBody());

	u8* msgBody = m_pMessage->getBody();
	return msgBody + pos;
}
