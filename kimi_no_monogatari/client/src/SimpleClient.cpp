#include "pch/pch.h"

#include "SimpleClient.h"

#include "ConnectionManager.h"
#include "RenderContext.h"
#include "GraphicsWorld.h"

SimpleClient::SimpleClient(RenderContext* renderContext, ConnectionManager& connectionManager)
:Client(renderContext)
,r_connectionManager(connectionManager)
{

}

SimpleClient::~SimpleClient()
{

}

void SimpleClient::update(float)
{
	
}

bool SimpleClient::init()
{
	// split into small pieces.
	if (!setupConnection())
	{
		return false;
	}
	if (!initGraphics())
	{
		return false;
	}
	if (!initGame())
	{
		return false;
	}
	return true;
}

bool SimpleClient::setupConnection()
{
	m_connection = r_connectionManager.createConnection();
	m_connection->setMessageHandler(boost::bind(&SimpleClient::handleGameMessage, this, _1));
	if (!m_connection->connect())
	{
		r_connectionManager.removeConnection(m_connection);
		return false;
	}
	return true;
}

void SimpleClient::handleGameMessage(Message* )
{
	// m_game->onMessage();
	// message->dispose();
}

bool SimpleClient::initGraphics()
{
	m_graphicsWorld = m_renderContext->getGraphicsWorld();
	return locateResources() && loadResources();
}

bool SimpleClient::initGame()
{
//	m_game = new WolfGame();
	return true;
}

bool SimpleClient::locateResources()
{
	return m_graphicsWorld->locateResources("resources.cfg");
}

bool SimpleClient::loadResources()
{
	return m_graphicsWorld->loadAllResources();
}
