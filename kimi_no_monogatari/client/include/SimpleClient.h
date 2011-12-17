#ifndef _SIMPLE_CLIENT_H_
#define _SIMPLE_CLIENT_H_

#include "Client.h"

class SimpleClient : public Client
{
public:
	SimpleClient(RenderContext* renderContext);
	virtual void update(float);
	virtual bool init();

};

#endif /* _SIMPLE_CLIENT_H_ */
