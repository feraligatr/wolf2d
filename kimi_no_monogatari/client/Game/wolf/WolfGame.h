#ifndef _WOLF_GAME_H_
#define _WOLF_GAME_H_

#include "Game.h"

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
	bool init();

private:
	void prepareResources();

#ifdef _FAKE_
	void fakeResources();
#endif /* _FAKE_ */

	GWScene* m_scene;

	WolfPlayer* m_player;

	typedef std::vector<WolfEnemy*> EnemyList;
	EnemyList m_enemys;

};

#endif /* _WOLF_GAME_H_ */
