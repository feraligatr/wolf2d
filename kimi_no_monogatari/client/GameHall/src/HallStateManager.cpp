#include "pch/pch.h"
#include <QLabel>

#include "HallStateManager.h"
#include "HallLoginState.h"
#include "HallHallState.h"
#include "HallGameState.h"
#include "GameHallApplication.h"

namespace hall
{

StateManager::StateManager()
:m_currentState(STATE_NULL)
{
	memset(m_states, 0, sizeof(State*) * STATE_NUM);
}

StateManager::~StateManager()
{
	if (m_currentState != STATE_NULL && m_states[m_currentState] != NULL)
	{
		ASSERT(m_states[m_currentState]->exit() == GSTATUS_OK);
	}
	for (int i = 0; i < STATE_NUM; ++i)
	{
		delete m_states[i];
	}
}

GSTATUS StateManager::init(STATE startupState)
{
	switchState(startupState);
	return GSTATUS_OK;
}

QWidget* StateManager::getCurrentWindow()
{
	if (m_currentState == STATE_NULL || m_states[m_currentState] == NULL)
	{
		return NULL;
	}
	return m_states[m_currentState]->getWindow();
}

GSTATUS StateManager::switchState(STATE state)
{
	// TODO: exit can not success at once. so exit should be asyc function. 
	// need some messageloop infrastructure.
	ASSERT(state >= 0 && state < STATE_NUM);
	if (m_currentState == state)
	{
		return GSTATUS_OK;
	}
	if (m_currentState != STATE_NULL)
	{
		RETURN_IF_ERROR(m_states[m_currentState]->exit());
	}
	if (!m_states[state])
	{
		m_states[state] = createState(state);
		RETURN_ERR_IF_NULL(m_states[state]);
	}
	RETURN_IF_ERROR(m_states[state]->enter());
	m_currentState = state;
	// send app to update window.
	g_app->onSwitchStateFinished();
	return GSTATUS_OK;
}

void StateManager::onGenericMessage(const QString& msg, void* data)
{
	if (m_currentState == STATE_NULL || m_states[m_currentState] == NULL)
	{
		return;
	}
	return m_states[m_currentState]->onGenericMessage(msg, data);
}

State* StateManager::createState(STATE state)
{
	switch(state)
	{
	case LOGIN_STATE:
		return new LoginState();
	case HALL_STATE:
		return new HallState();
	case GAME_STATE:
		return new GameState();
	default:
		ASSERT(false);
	}
	return NULL;
}

void StateManager::onResizeEvent(QResizeEvent * event)
{
	if (m_currentState == STATE_NULL || m_states[m_currentState] == NULL)
	{
		return;
	}
	m_states[m_currentState]->onResizeEvent(event);
}

}
