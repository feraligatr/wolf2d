#ifndef _MESSAGE_PARSERS_H_
#define _MESSAGE_PARSERS_H_

#include "msg/MessageDefine.h"
#include "msg/MessageParser.h"

class LoginMessageParser: public MessageParser
{
public:
	LoginMessageParser(Message* message)
		: MessageParser(message) {}
	virtual ~LoginMessageParser() {}
private:
	static void* operator new (size_t size) {return NULL;}
	static void operator delete (void *p) {}

protected:
	static const int FIELD_STR_USERNAME_POS = 0;
	static const int FIELD_STR_USERNAME_LEN = 20;
	static const int MESSAGE_LEN = 20;
	static const int MESSAGE_TYPE = MESSAGE_LOGIN;
public:
	const char* getUsername() { return getStr(FIELD_STR_USERNAME_POS); }
	void setUsername(const char* username) { setStr(username, FIELD_STR_USERNAME_POS, FIELD_STR_USERNAME_LEN); }
};

class EchoMessageParser: public MessageParser
{
public:
	EchoMessageParser(Message* message)
		: MessageParser(message) {}
	virtual ~EchoMessageParser() {}
private:
	static void* operator new (size_t size) {return NULL;}
	static void operator delete (void *p) {}

protected:
	static const int FIELD_STR_TEXT_POS = 0;
	static const int FIELD_STR_TEXT_LEN = 100;
	static const int MESSAGE_LEN = 100;
	static const int MESSAGE_TYPE = MESSAGE_ECHO;
public:
	const char* getText() { return getStr(FIELD_STR_TEXT_POS); }
	void setText(const char* text) { setStr(text, FIELD_STR_TEXT_POS, FIELD_STR_TEXT_LEN); }
};

#endif /*  _MESSAGE_PARSERS_H_ */