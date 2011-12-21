#include "pch/pch.h"
#include "GameHallApplication.h"
#include "GameHallService.h"
#include "AsioConnectionManager.h"

#include <QApplication>

#include <QTimer>

using namespace hall;

#define TWEAK_CONNECTION_UPDATE_INTERVAL 20

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
	delete m_connectionManager;
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
	m_connectionManager = new AsioConnectionManager();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(connection_update()));
	timer->start(TWEAK_CONNECTION_UPDATE_INTERVAL);
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

void GameHallApplication::connection_update()
{
	((AsioConnectionManager*)m_connectionManager)->update();
}
