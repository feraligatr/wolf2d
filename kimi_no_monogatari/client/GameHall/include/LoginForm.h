#ifndef _LOGIN_FORM_H_
#define _LOGIN_FORM_H_

#include <QLineEdit>
#include <QWidget>

#include "WidgetListener.h"

class LoginForm : public QWidget
{
	Q_OBJECT

public:
	LoginForm(WidgetListener* listener);
	void setupUI();

	QString getPasswd() const;
	QString getUsername() const;
	void clear();
	GSTATUS init(const QString& username, const QString& passwd);

private slots:
	void ok();
	void cancel();

private:
	QLineEdit *m_text_username;
	QLineEdit *m_text_passwd;

	WidgetListener* m_listener;
};


#endif /* _LOGIN_FORM_H_ */