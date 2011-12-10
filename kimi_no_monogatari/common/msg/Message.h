#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "msg/MessageDefine.h"

class MessageHeader
{
public:
	MessageHeader::MessageHeader()
		:m_size(0), m_type(MESSAGE_INVALID) {}

	explicit MessageHeader(int type, u32 size)
		:m_size(size), m_type(type) {}

	u32 getSize() const {
		return m_size;
	}

	int getType() const {
		return m_type;
	}

	void setType(int type) {
		m_type = type;
	}

	void setSize(u32 size) {
		m_size = size;
	}

	u32 m_size;
	int m_type;
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

	int getType() const {
		return ((MessageHeader*)m_buffer)->getType();
	}
	
	void setType(int type) {
		((MessageHeader*)m_buffer)->setType(type);
	}

	void setBodySize(u32 size) {
		((MessageHeader*)m_buffer)->setSize(size);
	}

	void setHeader(const MessageHeader& header);
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