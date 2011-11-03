#ifndef _HALL_HALL_STATE_H_
#define _HALL_HALL_STATE_H_

#include "HallState.h"

namespace hall
{

class HallState : public State, public WidgetListener
{
public:
	virtual GSTATUS exit();
	virtual GSTATUS enter();

	virtual void onGenericMessage(const QString& msg, void* data);
	virtual void onInvoked(QWidget* owner, QWidget* sender, QString msg, void* data);

private:
	QString m_lastSelectedName;
};

}


#endif /* _HALL_HALL_STATE_H_ */