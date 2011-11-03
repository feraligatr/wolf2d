#include "pch.h"

#include <QMessageBox>

#include "LoginForm.h"
#include "HallLoginState.h"
#include "GameHallApplication.h"

namespace hall
{

GSTATUS LoginState::exit()
{
	delete m_window;
	m_window = NULL;
	return GSTATUS_OK;
}

GSTATUS LoginState::enter()
{
	LoginForm* loginForm = new LoginForm(this);
	m_window = loginForm;
	return loginForm->init(m_username, m_passwd);
}

void LoginState::onInvoked(QWidget* owner, QWidget* , QString msg, void* )
{
	LoginForm* loginForm = (LoginForm*)owner;
	ASSERT(owner == m_window);
	if (msg == "ok")
	{
		m_username = loginForm->getUsername();
		m_passwd = loginForm->getPasswd();
		login(m_username, m_passwd);
	}
	else if (msg == "cancel")
	{
		loginForm->clear();
	}
}

void LoginState::login(const QString& username, const QString& passwd)
{
	if (username.length() > 0 && passwd.length() > 0)
	{
		g_app->login(username, passwd);
	}
}

void LoginState::onGenericMessage(const QString& msg, void*)
{
	// do nothing.
	if (msg == "log_success")
	{

	}
	else if (msg == "log_failed")
	{
		QMessageBox box(QMessageBox::Warning, "error", "login error, please relogin.");
		box.show();
	}
}

}
