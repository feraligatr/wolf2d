#ifndef _GAME_H_
#define _GAME_H_

#include "InputDefine.h"
#include "msg/Message.h"

class GraphicsWorld;
namespace tree
{
class PhysicsWorld;
}

class Game
{
public:
	Game(GraphicsWorld& gw, tree::PhysicsWorld& pw)
		:r_gw(gw), r_pw(pw)
		{}
	virtual ~Game() {}

	virtual void onMouseEvent(tree::MouseEvent& evt) = 0;
	virtual void onKeyEvent(tree::KeyEvent& evt) = 0;
	virtual void onHandleMessage(Message* message) = 0;

	virtual void update(float dt) = 0;
	virtual bool init() = 0;

protected:
	GraphicsWorld& r_gw;
	tree::PhysicsWorld& r_pw;
};

#endif /* _GAME_H_ */
