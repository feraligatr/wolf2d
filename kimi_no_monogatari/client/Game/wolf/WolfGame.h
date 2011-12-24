#ifndef _WOLF_GAME_H_
#define _WOLF_GAME_H_

#include "Game.h"

class WolfGame : public Game
{
public:
	WolfGame(GraphicsWorld& gw);
	virtual ~WolfGame();

	virtual void onMouseEvent(tree::MouseEvent& evt);
	virtual void onKeyEvent(tree::KeyEvent& evt);
	virtual void onHandleMessage(Message* message);

	virtual void update(float dt);
};

#endif /* _WOLF_GAME_H_ */
