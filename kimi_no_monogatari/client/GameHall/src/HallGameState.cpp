#include "pch.h"

#include "HallWindow.h"
#include "HallGameState.h"
#include "GameGLWidget.h"
#include "Sample3dGame.h"
#include "GameHallApplication.h"

namespace hall
{

GameState::GameState()
:m_currentGame(NULL)
{

}

GSTATUS GameState::exit()
{
	if (m_currentGame)
	{
		// TODO: exit should be asyc, invoke m_currentGame->exit() and wait the exit success message to come back.
		delete m_currentGame;
		m_currentGame = NULL;
	}
	delete m_window;
	m_window = NULL;
	return GSTATUS_OK;
}

GSTATUS GameState::enter()
{
	// TODO: by parameter to create different GameContent and Game.
	m_window = new GameGLWidget(this);
	m_currentGame = new Sample3DGame(this, this);
	m_currentGame->start(m_window->width(), m_window->height());
	m_time = QTime::currentTime();
	m_time.start();

	return GSTATUS_OK;
}

void GameState::onInvoked(QWidget* owner, QWidget* , QString msg, void* data)
{
	ASSERT(owner == m_window);
	if (msg == "update")
	{
		m_currentGame->update(m_time.restart() / 1000.0f);
	}
	else if (msg == "paint")
	{
		m_currentGame->update(0);
	}
	else if (msg == "resize")
	{
		QSize* size = (QSize*)data;
		m_currentGame->resize(size->width(), size->height());
	}
}

void GameState::onGenericMessage(const QString& , void*)
{
	// do nothing
}

void GameState::onResizeEvent(QResizeEvent * )
{
	// TODO: resize the widget 
}

int GameState::getWindowId()
{
	return (size_t)(HWND)(m_window->winId());
}

void GameState::changeWindowId(int )
{
	m_window->setAttribute( Qt::WA_PaintOnScreen, true );
	m_window->setAttribute( Qt::WA_NoBackground );
}

}