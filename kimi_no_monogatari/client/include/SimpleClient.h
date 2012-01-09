#ifndef _SIMPLE_CLIENT_H_
#define _SIMPLE_CLIENT_H_

#include "Client.h"

#include "Msg/MessageDispatcher.h"
#include "InputDefine.h"

class ConnectionManager;
class GraphicsWorld;
class Game;

namespace tree
{
	class PhysicsWorld;
}

class SimpleClient : public Client
{
public:
	SimpleClient(RenderContext* renderContext, ConnectionManager& connectionManager);
	virtual ~SimpleClient();
	virtual void update(float);
	virtual bool init();

	void onGameMessage(Message* message);
	void onMouseEvent(tree::MouseEvent& evt);
	void onKeyEvent(tree::KeyEvent& evt);

protected:
	bool setupConnection();
	bool initGraphics();
	bool initGame();


	bool locateResources();
	bool loadResources();

protected:
	ConnectionManager& r_connectionManager;
	ConnectionPtr m_connection;

	Game* m_game;

	GraphicsWorld* m_gameGW;
	tree::PhysicsWorld* m_pw;

};

#endif /* _SIMPLE_CLIENT_H_ */
