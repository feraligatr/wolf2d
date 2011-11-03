#ifndef _HALL_LOGIN_STATE_H_
#define _HALL_LOGIN_STATE_H_


#include "HallState.h"
#include "WidgetListener.h"

namespace hall
{

class LoginState : public State, public WidgetListener
{
public:
	virtual GSTATUS exit();
	virtual GSTATUS enter();

	virtual void onGenericMessage(const QString& msg, void* data);
	virtual void onInvoked(QWidget* owner, QWidget* sender, QString msg, void* data);

private:
	void login(const QString& username, const QString& passwd);

	QString m_username;
	QString m_passwd;
};

}

#endif /* _HALL_LOGIN_STATE_H_ */
