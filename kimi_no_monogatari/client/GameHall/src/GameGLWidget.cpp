#include "pch/pch.h"

#include "GameGLWidget.h"

#include "InputDefine.h"

#ifndef TWEAK_GAME_UPDATE_INTERVAL
#define TWEAK_GAME_UPDATE_INTERVAL (1000/60)
#endif /* TWEAK_GAME_UPDATE_INTERVAL */

GameGLWidget::GameGLWidget(WidgetListener* listener)
:m_listener(listener)
,m_client(NULL)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout_update()));
	timer->start(TWEAK_GAME_UPDATE_INTERVAL);
}

void GameGLWidget::setClient(SimpleClient* client)
{
	m_client = client;
}

void GameGLWidget::initializeGL()
{
	m_listener->onInvoked(this, NULL, "init", NULL);
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

void GameGLWidget::recreateFromOgreWindow(WId wid)
{
//	this->create(wid);
}

void GameGLWidget::mousePressEvent(QMouseEvent *evt)
{
	tree::MouseEvent::ButtonType type;
	switch(evt->button())
	{
	case Qt::LeftButton:
		type = tree::MouseEvent::BT_LEFT;
		break;
	case Qt::RightButton:
		type = tree::MouseEvent::BT_RIGHT;
		break;
	case Qt::MidButton:
		type = tree::MouseEvent::BT_MIDDLE;
		break;
	default:
		return;
	}

	tree::MouseEvent mevt(evt->pos().x(), evt->pos().y(), type, tree::MouseEvent::ACT_PRESS);
	if (m_client)
	{
		m_client->onMouseEvent(mevt);
	}
}

void GameGLWidget::mouseReleaseEvent(QMouseEvent *evt)
{
	tree::MouseEvent::ButtonType type;
	switch(evt->button())
	{
	case Qt::LeftButton:
		type = tree::MouseEvent::BT_LEFT;
		break;
	case Qt::RightButton:
		type = tree::MouseEvent::BT_RIGHT;
		break;
	case Qt::MidButton:
		type = tree::MouseEvent::BT_MIDDLE;
		break;
	default:
		return;
	}

	tree::MouseEvent mevt(evt->pos().x(), evt->pos().y(), type, tree::MouseEvent::ACT_RELEASE);
	if (m_client)
	{
		m_client->onMouseEvent(mevt);
	}
}

void GameGLWidget::mouseDoubleClickEvent(QMouseEvent *evt)
{
	tree::MouseEvent::ButtonType type;
	switch(evt->button())
	{
	case Qt::LeftButton:
		type = tree::MouseEvent::BT_LEFT;
		break;
	case Qt::RightButton:
		type = tree::MouseEvent::BT_RIGHT;
		break;
	case Qt::MidButton:
		type = tree::MouseEvent::BT_MIDDLE;
		break;
	default:
		return;
	}

	tree::MouseEvent mevt(evt->pos().x(), evt->pos().y(), type, tree::MouseEvent::ACT_DOUBLE_CLICK);
	if (m_client)
	{
		m_client->onMouseEvent(mevt);
	}
}

void GameGLWidget::mouseMoveEvent(QMouseEvent *evt)
{
	tree::MouseEvent mevt(evt->pos().x(), evt->pos().y(), tree::MouseEvent::BT_LEFT, tree::MouseEvent::ACT_MOVE);
	if (m_client)
	{
		m_client->onMouseEvent(mevt);
	}
}

#ifndef QT_NO_WHEELEVENT
void GameGLWidget::wheelEvent(QWheelEvent *)
{
	// ignore
}
#endif
void GameGLWidget::keyPressEvent(QKeyEvent *evt)
{
	tree::KeyEvent kevt(evt->key(), tree::KeyEvent::ACT_PRESS);
	if (m_client)
	{
		m_client->onKeyEvent(kevt);
	}
}

void GameGLWidget::keyReleaseEvent(QKeyEvent *evt)
{
	tree::KeyEvent kevt(evt->key(), tree::KeyEvent::ACT_RELEASE);
	if (m_client)
	{
		m_client->onKeyEvent(kevt);
	}
}

