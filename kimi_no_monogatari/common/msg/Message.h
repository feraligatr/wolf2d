#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "msg/MessageDefine.h"

// TODO: change to template<u32 capacity>Message?
//
// the message is mainly a buffer, so no derived message.

class MessageHeader
{
public:
	MessageHeader::MessageHeader()
		:m_size(0), m_type(MESSAGE_INVALID) {}

	u32 getSize() const {
		return m_size;
	}

	MessageType getType() const {
		return m_type;
	}

	u32 m_size;
	MessageType m_type;
};

class Message
{
public:
	friend class MessageManager;

	u32 getBodySize() const {
		return ((MessageHeader*)m_buffer)->getSize();
	}

	u32 getBufferSize() const {
		return getBodySize() + sizeof(MessageHeader);
	}

	u8* getBody() {
		return m_buffer + sizeof(MessageHeader);
	}

	// header + body.
	u8* getBuffer() {
		return m_buffer;
	}

	u32 getCapacity() const {
		return m_capacity;
	}

	MessageType getMessageType() const {
		return ((MessageHeader*)m_buffer)->getType();
	}
	
	void setMessageHeader(const MessageHeader& header);
	void dispose();

protected:
	Message(MessageManager* manager, u32 capacity);

	~Message();

private:
	u8* m_buffer;
	u32 m_capacity;
	MessageManager* m_manager;
};


#endif