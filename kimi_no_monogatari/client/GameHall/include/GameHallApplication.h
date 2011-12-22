#ifndef _GAME_HALL_APPLICATION_H_
#define _GAME_HALL_APPLICATION_H_

#include <QApplication>

#include "HallStateManager.h"
#include "GameHallWindow.h"

class GameHallService;
class ConnectionManager;

class GameHallApplication : public QApplication
{
	Q_OBJECT
public:
	GameHallApplication(int argc, char *argv[]);
	virtual ~GameHallApplication();
	virtual GSTATUS init();
	virtual int run();

	inline hall::StateManager* getStateManager() {
		return m_stateManager;
	}

	ConnectionManager& getConnectionManager() {
		return *m_connectionManager;
	}

	GameHallService& getService() {
		return *m_gameService;
	}

	void login(const QString& username, const QString& passwd);
	void selectGame(const QString& gamename);
	
	void onSwitchStateFinished();
	void onResizeEvent(QResizeEvent * event);

private slots:
	void connection_update();

private:
	GameHallWindow *m_win;
	hall::StateManager *m_stateManager;
	GameHallService* m_gameService;
	ConnectionManager* m_connectionManager;
};

extern GameHallApplication *g_app;

#endif /* _GAME_HALL_APPLICATION_H_ */

