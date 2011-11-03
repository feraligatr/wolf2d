#include "pch.h"

#include "GameHallService.h"
#include "GameHallApplication.h"
#include "HallStateManager.h"

using namespace hall;

GameHallService::GameHallService(GameHallApplication* app)
:m_app(app)
,m_connected(FALSE)
{

}

void GameHallService::login(const QString& username, const QString& passwd)
{
//  current fake success.after serverl seconds.
	m_username = username;
	m_passwd = passwd;
	loginSuccess();
}

void GameHallService::loginSuccess()
{
	m_connected = true;
	m_app->getStateManager()->onGenericMessage("log_success", NULL);
	m_app->getStateManager()->switchState(StateManager::HALL_STATE);
}

void GameHallService::loginFailed()
{
	m_connected = false;
	m_app->getStateManager()->onGenericMessage("log_failed", NULL);
}

void GameHallService::selectGame(const QString& gamename)
{
	// here to search the available games, and do some other work.
	m_currentGameName = gamename;
	m_app->getStateManager()->onGenericMessage("gamestart", &m_currentGameName);
}