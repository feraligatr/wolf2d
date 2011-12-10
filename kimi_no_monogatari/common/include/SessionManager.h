#ifndef _SESSION_MANAGER_H_
#define _SESSION_MANAGER_H_

#include "TypeDefine.h"
#include "Session.h"

class SessionManager
{
public:
	void start(SessionPtr session);
	void stop(SessionPtr session);
	void stopAll();

	typedef std::set<SessionPtr> SessionSet;

private:
	SessionSet m_sessions;
};


#endif /* _SESSION_MANAGER_H_ */