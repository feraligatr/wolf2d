#ifndef _GAME_HALL_APPLICATION_H_
#define _GAME_HALL_APPLICATION_H_

#include <QApplication>

#include "HallStateManager.h"
#include "GameHallWindow.h"

class GameHallService;

class GameHallApplication : public QApplication
{
public:
	GameHallApplication(int argc, char *argv[]);
	virtual ~GameHallApplication();
	virtual GSTATUS init();
	virtual int run();

	inline hall::StateManager* getStateManager() {
		return m_stateManager;
	}

	void login(const QString& username, const QString& passwd);
	void selectGame(const QString& gamename);
	
	void onSwitchStateFinished();
	void onResizeEvent(QResizeEvent * event);

private:
	GameHallWindow *m_win;
	hall::StateManager *m_stateManager;
	GameHallService* m_gameService;
};

extern GameHallApplication *g_app;

#endif /* _GAME_HALL_APPLICATION_H_ */

