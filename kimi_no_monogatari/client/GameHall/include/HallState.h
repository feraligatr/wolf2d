#ifndef _HALL_STATE_H_
#define _HALL_STATE_H_

#include <QWidget>

namespace hall
{

class State
{
public:
	virtual GSTATUS exit() = 0;
	virtual GSTATUS enter() = 0;
	virtual void onGenericMessage(const QString& msg, void* data) = 0;
	virtual void onResize(const QSize& ) {}

	virtual void onSwitchStateFinished() {}

	inline QWidget* getWindow() {
		return m_window;
	}

protected:
	QWidget* m_window;

};


}


#endif /* _HALL_STATE_H_ */