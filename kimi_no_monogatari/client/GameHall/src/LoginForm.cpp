#include "pch/pch.h"

#include <QLabel>
#include <QDialogButtonBox>

#include "LoginForm.h"

LoginForm::LoginForm(WidgetListener* listener)
:m_listener(listener)
{
	setupUI();
}

void LoginForm::setupUI()
{
	setWindowTitle("Login");
	resize(272, 127);
	m_text_username = new QLineEdit(this);
	m_text_username->setGeometry(QRect(112, 20, 121, 20));
	m_text_passwd = new QLineEdit(this);
	m_text_passwd->setGeometry(QRect(112, 50, 121, 20));
	m_text_passwd->setEchoMode(QLineEdit::Password);
	QLabel* label_username = new QLabel(this);
	label_username->setGeometry(QRect(30, 20, 61, 16));
	QLabel* label_passwd = new QLabel(this);
	label_passwd->setGeometry(QRect(30, 50, 54, 12));

	label_username->setText("Username:");
	label_passwd->setText("Password:");

	QDialogButtonBox* okcancel = new QDialogButtonBox(this);
	okcancel->setGeometry(QRect(60, 90, 156, 23));
	okcancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

	QObject::connect(okcancel, SIGNAL(accepted()), this, SLOT(ok()));
	QObject::connect(okcancel, SIGNAL(rejected()), this, SLOT(cancel()));
}

void LoginForm::ok()
{
	if (m_listener)
	{
		m_listener->onInvoked(this, NULL, "ok", NULL);
	}
}

void LoginForm::cancel()
{
	if (m_listener)
	{
		m_listener->onInvoked(this, NULL, "cancel", NULL);
	}
}

QString LoginForm::getPasswd() const
{
	return m_text_username->text();
}

QString LoginForm::getUsername() const
{
	return m_text_passwd->text();
}

void LoginForm::clear()
{
	m_text_username->clear();
	m_text_passwd->clear();
}

GSTATUS LoginForm::init(const QString& username, const QString& passwd)
{
	m_text_username->setText(username);
	m_text_passwd->setText(passwd);
	return GSTATUS_OK;
}

