#include "pch/pch.h"

#include "GameGLWidget.h"

#include <QResizeEvent>

#ifndef TWEAK_GAME_UPDATE_INTERVAL
#define TWEAK_GAME_UPDATE_INTERVAL (1000/60)
#endif /* TWEAK_GAME_UPDATE_INTERVAL */

GameGLWidget::GameGLWidget(WidgetListener* listener)
:m_listener(listener)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout_update()));
	timer->start(TWEAK_GAME_UPDATE_INTERVAL);
}

void GameGLWidget::initializeGL()
{
	
}

void GameGLWidget::resizeGL(int w, int h)
{
	QSize size(w, h);
	m_listener->onInvoked(this, NULL, "resize", &size);
}

void GameGLWidget::paintGL()
{
	m_listener->onInvoked(this, NULL, "paint", NULL);
}

void GameGLWidget::timeout_update()
{
	m_listener->onInvoked(this, NULL, "update", NULL);
}
