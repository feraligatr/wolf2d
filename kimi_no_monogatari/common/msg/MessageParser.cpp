#include "common.h"

#include <string.h>
#include "msg/Message.h"
#include "msg/MessageParser.h"

MessageParser::MessageParser(Message* message)
:m_pMessage(message)
{
}

MessageParser::~MessageParser()
{
}

void MessageParser::setData(u32 pos, const void* data, u32 len)
{
	ASSERT(len > 0 && data);
	ASSERT(m_pMessage && m_pMessage->getBodySize() >= pos + len && m_pMessage->getBody());

	u8* msgBody = m_pMessage->getBody();
	memcpy(msgBody + pos, data, len);
}

const void* MessageParser::getData(u32 pos)
{
	ASSERT(m_pMessage && m_pMessage->getBodySize() > pos && m_pMessage->getBody());

	u8* msgBody = m_pMessage->getBody();
	return msgBody + pos;
}

void MessageParser::setStr(const char* str, u32 pos, u32 len)
{
	u32 slen = strlen(str);
	ASSERT(slen < len);
	setData(pos, str, slen);
}

const char* MessageParser::getStr(u32 pos)
{
	return (const char*) getData(pos);
}
