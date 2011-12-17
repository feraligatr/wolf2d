#ifndef _HALL_GAME_STATE_H_
#define _HALL_GAME_STATE_H_

#include "HallState.h"
#include "Game.h"

#include <QTime>

namespace hall
{

class GameState : public State, public WidgetListener, public GameContext, public GameListener
{
public:
	GameState();
	virtual GSTATUS exit();
	virtual GSTATUS enter();

	virtual void onGenericMessage(const QString& msg, void* data);
	virtual void onInvoked(QWidget* owner, QWidget* sender, QString msg, void* data);

	virtual void onResizeEvent(QResizeEvent * event);

	virtual int getWindowId();

	virtual void changeWindowId(int windowId);

private:
	// implement a parameter list to start different games.
	// each game may need a different render context(qt, 2d, 3d, opengl, directx)
	// gamename, server, id....
	// other limitation or something.

	// current the game will be wolf2d.
	// all game specific details controlled by game. here only load dll and new a game.
	// then delegate all events to games, and give render context to game.

	// TODO GameState should derive from a interface like GameContent, so all game get
	// needed resource from GameContent. 

	// TODO GameState should implement a GameListener and register to Game, so game can 
	// send message back.

	// TODO should use delegate for GameContent and GameListener
	// but for simplicity, we inherit the two interface.
	// dont use delegate util we have enough apis.

	Game* m_currentGame;

	QTime m_time;

};

}


#endif /* _HALL_GAME_STATE_H_ */