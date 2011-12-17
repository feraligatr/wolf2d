#ifndef _MESSAGE_PARSER_H_
#define _MESSAGE_PARSER_H_

class Message;

class MessageParser
{
public:
	MessageParser(Message* message);
	virtual ~MessageParser();

	Message* getMessage() { return m_pMessage; }
private:
	static void* operator new (size_t ) {return NULL;}
	static void operator delete (void *) {}
protected:
	Message* m_pMessage;

	void setData(u32 pos, const void* data, u32 len);
	const void *getData(u32 pos);

	void setStr(const char* str, u32 pos, u32 len);
	const char* getStr(u32 pos);
};

#endif /* _MESSAGE_PARSER_H_ */
