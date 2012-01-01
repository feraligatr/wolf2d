#include "pch/pch.h"

#include "HallWindow.h"
#include "HallGameState.h"
#include "GameGLWidget.h"
#include "GameHallApplication.h"

#include "OgreRenderContext.h"
#include "SimpleClient.h"

namespace hall
{

GameState::GameState()
	:m_currentClient(NULL),
	 m_renderContext(NULL)
{

}

GSTATUS GameState::exit()
{
	if (m_currentClient)
	{
		// TODO: exit should be asyc, invoke m_currentClient->exit() and wait the exit success message to come back.
		delete m_currentClient;
		m_currentClient = NULL;
	}
	if (m_renderContext)
	{
		delete m_renderContext;
		m_renderContext = NULL;
	}
	delete m_window;
	m_window = NULL;
	return GSTATUS_OK;
}

GSTATUS GameState::enter()
{
	// TODO: by parameter to create different GameContent and Game.
	m_window = new GameGLWidget(this);
	
	return GSTATUS_OK;
}

void GameState::onInvoked(QWidget* owner, QWidget* , QString msg, void* data)
{
	ASSERT(owner == m_window);
	if (msg == "create_window")
	{
		m_renderContext = new OgreRenderContext((size_t)(HWND)(m_window->parentWidget()->winId()));
		m_renderContext->start(m_window->width(), m_window->height());

		((GameGLWidget*)m_window)->recreateFromOgreWindow(((OgreRenderContext*)m_renderContext)->getWindowId());
		m_window->setAttribute( Qt::WA_PaintOnScreen, true );
		m_window->setAttribute( Qt::WA_NoBackground );

		m_currentClient = new SimpleClient(m_renderContext, g_app->getConnectionManager());
		// got username from g_app->getService()->getUserName();

		if (!m_currentClient->init())
		{
			
		}
		m_time = QTime::currentTime();
		m_time.start();
	}
	if (!m_currentClient)
	{
		return;
	}
	if (msg == "update")
	{
		m_currentClient->update(m_time.restart() / 1000.0f);
		m_renderContext->render();
	}
	else if (msg == "paint")
	{
		m_renderContext->render();
	}
	else if (msg == "resize")
	{
		QSize* size = (QSize*)data;
		m_renderContext->resize(size->width(), size->height());
	}
	else if (msg == "init")
	{

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

}
