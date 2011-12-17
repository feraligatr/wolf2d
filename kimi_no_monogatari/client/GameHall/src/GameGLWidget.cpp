#include "pch/pch.h"

#include "GameGLWidget.h"

#include <QResizeEvent>


GameGLWidget::GameGLWidget(WidgetListener* listener)
:m_listener(listener)
{
	
}

void GameGLWidget::timerEvent(QTimerEvent* )
{
	m_listener->onInvoked(this, NULL, "update", NULL);
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
