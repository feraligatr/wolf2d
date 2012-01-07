#ifndef _HALL_STATE_MANAGER_H_
#define _HALL_STATE_MANAGER_H_

#include <QWidget>

#include "HallState.h"

namespace hall
{

class StateManager
{
public:
	enum STATE
	{
		LOGIN_STATE,
		HALL_STATE,
		GAME_STATE,
		STATE_NUM,
		STATE_NULL
	};

	StateManager();
	~StateManager();

	GSTATUS init(STATE startupState);
	QWidget* getCurrentWindow();

	GSTATUS switchState(STATE startupState);

	void onGenericMessage(const QString& msg, void* data);

	void onResize(const QSize& size);

private:
	State* createState(STATE state);

private:
	State* m_states[STATE_NUM];
	STATE m_currentState;

};

}

#endif /* _HALL_STATE_MANAGER_H_ */
