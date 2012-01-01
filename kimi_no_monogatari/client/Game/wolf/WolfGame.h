#ifndef _WOLF_GAME_H_
#define _WOLF_GAME_H_

#include "Game.h"
#include "renderer/Graphics.h"

class WolfPlayer;
class WolfEnemy;
class GWCamera;

// This is the pure game, not including any menu and overlay outof game like pause menu or end menu. 

class WolfGame : public Game
{
public:
	WolfGame(GraphicsWorld& gw);
	virtual ~WolfGame();

	virtual void onMouseEvent(tree::MouseEvent& evt);
	virtual void onKeyEvent(tree::KeyEvent& evt);
	virtual void onHandleMessage(Message* message);

	virtual void update(float dt);

	// TODO: need istream to read.
	virtual bool init();
private:
#ifdef _FAKE_
	void fakeResources();
#endif /* _FAKE_ */

	// will be replaced by more concrete camera which will take more parameter and more intellegent.
	GWCamera* m_camera;

	WolfPlayer* m_player;

	typedef std::vector<WolfEnemy*> EnemyList;
	EnemyList m_enemys;

};

#endif /* _WOLF_GAME_H_ */
