#ifndef _MESSAGE_PARSER_H_
#define _MESSAGE_PARSER_H_

class Message;

class MessageParser
{
public:
	MessageParser(Message* message);
	virtual ~MessageParser();
private:
	static void* operator new (size_t size) {return NULL;}
	static void operator delete (void *p) {}
protected:
	void setData(u32 pos, void* data, u32 len);
	void *getData(u32 pos);
	Message* m_pMessage;
};

#endif /* _MESSAGE_PARSER_H_ */
