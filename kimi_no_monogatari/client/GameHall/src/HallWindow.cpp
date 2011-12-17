#include "pch/pch.h"

#include <QPushButton>
#include "HallWindow.h"

HallWindow::HallWindow(WidgetListener* listener)
:m_listener(listener)
{
	setupUI();
}

void HallWindow::setupUI()
{
	setWindowTitle("DULL");
	resize(254, 115);

	QPushButton* testbutton = new QPushButton(this);
	testbutton->setGeometry(QRect(80, 30, 111, 41));
	testbutton->setText("testgame");

	QObject::connect(testbutton, SIGNAL(clicked()), this, SLOT(onTestGame()));
}

void HallWindow::onTestGame()
{
	if (m_listener)
	{
		QString gamename = "testgame";
		m_listener->onInvoked(this, NULL, "selectgames", &gamename);
	}
}