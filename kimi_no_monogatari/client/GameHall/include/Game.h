#ifndef _GAME_H_
#define _GAME_H_

#include "GameContext.h"
#include "GameListener.h"

class Game
{
public:
	Game(GameContext* context, GameListener* listener) :m_paused(false), m_gameContext(context), m_gameListener(listener) {}
	// sample implement for a simple pause/resume. maybe removed and set as pure virtual.

	virtual void pause() {
		m_paused = true;
	}
	virtual void resume() {
		m_paused = false;
	}

	void update(float dt) {
		if (m_paused)
		{
			return;
		}
		intenal_update(dt);
	}

	virtual bool start(int width, int height) = 0;
	virtual void exit() = 0;
	virtual void resize(int width, int height) = 0;

protected:
	virtual void intenal_update(float dt) = 0;

	// pass other events to games.
	// mouse, key ...
	

protected:
	bool m_paused;

	GameContext* m_gameContext;
	GameListener* m_gameListener;
};


#endif /* _GAME_H_ */
