#include "pch/pch.h"
#include <QtGui>

#include "GameHallWindow.h"
#include "GameHallApplication.h"

GameHallWindow::GameHallWindow()
{
	m_centralWidget = new QWidget(this);
	setCentralWidget(m_centralWidget);
	resize(1024, 768);
}

void GameHallWindow::setDisplayWindow(QWidget* window)
{
	if (!window)
	{
		return;
	}
	int x = (width() - window->frameGeometry().width()) / 2;
	int y = (height() - window->frameGeometry().height()) / 2;
	window->setParent(m_centralWidget);
	window->move(x, y);
	window->show();
}

void GameHallWindow::resizeEvent(QResizeEvent * event)
{
	g_app->onResizeEvent(event);
}
