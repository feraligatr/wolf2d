#include "pch.h"

#include "HallWindow.h"
#include "HallHallState.h"
#include "GameHallApplication.h"

namespace hall
{

GSTATUS HallState::exit()
{
	delete m_window;
	m_window = NULL;
	return GSTATUS_OK;
}

GSTATUS HallState::enter()
{
	HallWindow* hallWindow = new HallWindow(this);
	m_window = hallWindow;
	return GSTATUS_OK;
}

void HallState::onInvoked(QWidget* owner, QWidget* , QString msg, void* data)
{
	ASSERT(owner == m_window);
	if (msg == "selectgames")
	{
		// tell application to select games.
		// void* contains game name
		QString* gamename = (QString*)data;
		m_lastSelectedName = *gamename;
		g_app->selectGame(m_lastSelectedName);
	}
}

void HallState::onGenericMessage(const QString& msg, void* data)
{
	// do nothing
	if (msg == "gamestart")
	{
		//void* contains detail information about the selection
		QString* gamename = (QString*)data;
		if (*gamename == "testgame")
		{
			g_app->getStateManager()->switchState(StateManager::GAME_STATE);
		}
	}
}

}

