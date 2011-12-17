#include "pch/pch.h"
#include "GameHallApplication.h"
#include "GameHallService.h"

using namespace hall;

GameHallApplication::GameHallApplication(int argc, char *argv[])
:QApplication(argc, argv)
,m_win(NULL)
,m_stateManager(NULL)
,m_gameService(NULL)
{
}

/* virtual */
GameHallApplication::~GameHallApplication()
{
	delete m_stateManager;
	delete m_win;
}

/* virtual */
GSTATUS GameHallApplication::init()
{
	setOrganizationName("Personal");
	setApplicationName("Game Hall");
	if (m_stateManager == NULL)
	{
		m_stateManager = new StateManager();
		m_stateManager->init(StateManager::LOGIN_STATE);
	}
	if (m_gameService == NULL)
	{
		m_gameService = new GameHallService(this);
	}
	if (m_win == NULL)
	{
		m_win = new GameHallWindow();
		m_win->setDisplayWindow(m_stateManager->getCurrentWindow());
	}
	m_win->show();
	return GSTATUS_OK;
}

/* virtual */
int GameHallApplication::run()
{
	return QApplication::exec();
}

void GameHallApplication::login(const QString& username, const QString& passwd)
{
	m_gameService->login(username, passwd);
}

void GameHallApplication::selectGame(const QString& gamename)
{
	m_gameService->selectGame(gamename);
}

void GameHallApplication::onSwitchStateFinished()
{
	if (m_win)
	{
		m_win->setDisplayWindow(m_stateManager->getCurrentWindow());
	}
}

void GameHallApplication::onResizeEvent(QResizeEvent * event)
{
	if (m_win)
	{
		m_stateManager->onResizeEvent(event);
	}
}

