#ifndef _SESSION_MANAGER_H_
#define _SESSION_MANAGER_H_

#include "TypeDefine.h"
#include "Session.h"

class SessionManager
{
public:
	virtual ~SessionManager();
	virtual void start(SessionPtr session);
	virtual void stop(SessionPtr session);
	virtual void stopAll();

	typedef std::set<SessionPtr> SessionSet;

private:
	SessionSet m_sessions;
};


#endif /* _SESSION_MANAGER_H_ */