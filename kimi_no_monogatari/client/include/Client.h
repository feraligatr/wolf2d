#ifndef _CLIENT_H_
#define _CLIENT_H_

class RenderContext;

class Client
{
public:
	Client(RenderContext* renderContext)
		:m_renderContext(renderContext)
	{}
	virtual ~Client() {}

	virtual void update(float interval) = 0;

	virtual bool init() = 0;

	// TODO: listeners.
	// virtual addClientListener(ClientListener*);
	// virtual removeClientListener(ClientListener*);
	
	RenderContext* m_renderContext;

};


#endif /* _CLIENT_H_ */
