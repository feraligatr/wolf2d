#ifndef _GAME_H_
#define _GAME_H_

#include "InputDefine.h"
#include "msg/Message.h"

class GraphicsWorld;

class Game
{
public:
	Game(GraphicsWorld& gw)
		:r_gw(gw) 
		{}
	virtual ~Game() {}

	virtual void onMouseEvent(tree::MouseEvent& evt) = 0;
	virtual void onKeyEvent(tree::KeyEvent& evt) = 0;
	virtual void onHandleMessage(Message* message) = 0;

	virtual void update(float dt) = 0;
	virtual bool init() = 0;

protected:
	GraphicsWorld& r_gw;
};

#endif /* _GAME_H_ */
