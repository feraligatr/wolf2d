#ifndef _WIDGET_LISTENER_H_
#define _WIDGET_LISTENER_H_

#include <QWidget>

class WidgetListener
{
public:
	virtual void onInvoked(QWidget* owner, QWidget* sender, QString msg, void* data) = 0;
};


#endif /* _WIDGET_LISTENER_H_ */

