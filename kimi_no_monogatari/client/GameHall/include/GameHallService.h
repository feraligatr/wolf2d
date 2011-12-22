#ifndef _GAME_HALL_SERVICE_H_
#define _GAME_HALL_SERVICE_H_

#include "GameHallApplication.h"

class GameHallApplication;

class GameHallService
{
public:
	GameHallService(GameHallApplication* app);

	void login(const QString& username, const QString& passwd);
	void selectGame(const QString& gamename);

	// callback, maybe other names.
	void loginSuccess();
	void loginFailed();

	const QString& getUserName() const {
		return m_username;
	}

private:
	GameHallApplication* m_app;

	QString m_username;
	QString m_passwd;
	
	QString m_currentGameName;
	// after we set up right network progress, this will be refactored.
	bool m_connected;
};


#endif /* _GAME_HALL_SERVICE_H_ */