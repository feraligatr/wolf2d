#ifndef _HALL_WINDOW_H_
#define _HALL_WINDOW_H_

#include <QWidget>

#include "WidgetListener.h"

class HallWindow : public QWidget
{
	Q_OBJECT

public:
	HallWindow(WidgetListener* listener);
	void setupUI();

private slots:
	void onTestGame();

private:
	WidgetListener* m_listener;
};


#endif /* _HALL_WINDOW_H_ */