#ifndef _DUMMY_MESSAGE_DISPATCHER_H_
#define _DUMMY_MESSAGE_DISPATCHER_H_

#include "MessageDispatcher.h"

class DummyMessageDispatcher : public MessageDispatcher
{
public:
	void dispatchMessage(Message* message);
};


#endif /* _DUMMY_MESSAGE_DISPATCHER_H_ */
