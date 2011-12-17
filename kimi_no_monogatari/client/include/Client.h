#ifndef _CLIENT_H_
#define _CLIENT_H_

class Client
{
public:
	virtual ~Client() {}
	virtual void update(float interval) = 0;
	virtual bool init() = 0;
};


#endif /* _CLIENT_H_ */
