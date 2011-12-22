#ifndef _SIMPLE_CLIENT_H_
#define _SIMPLE_CLIENT_H_

#include "Client.h"

#include "Msg/MessageDispatcher.h"

class ConnectionManager;
class GraphicsWorld;
class Game;

class SimpleClient : public Client
{
public:
	SimpleClient(RenderContext* renderContext, ConnectionManager& connectionManager);
	virtual ~SimpleClient();
	virtual void update(float);
	virtual bool init();

	void handleGameMessage(Message* message);
protected:
	bool setupConnection();
	bool initGraphics();
	bool initGame();


	bool locateResources();
	bool loadResources();

protected:
	ConnectionManager& r_connectionManager;
	ConnectionPtr m_connection;

	GraphicsWorld* m_graphicsWorld;
	Game* m_game;

};

#endif /* _SIMPLE_CLIENT_H_ */
