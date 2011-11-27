#ifndef _SERVER_H_
#define _SERVER_H_

#include "Session.h"

class SessionManager;

class Server
{
public:
	static Server* getInstance();

	virtual Session* getNewSession(boost::asio::io_service& io_service) = 0;

	// update everything every interval time.
	// TODO: add float inerval as update parameter. ? or get interval from other place?
	virtual void update() = 0;
	virtual SessionManager* getSessionManager() = 0;
	virtual void destroy() = 0;

protected:
	Server() {}
	~Server() {}

private:
	static Server* m_instance;
};

#endif /* _SERVER_H_ */
