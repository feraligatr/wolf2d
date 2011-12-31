#include "pch/pch.h"

#include "SimpleClient.h"

#include "ConnectionManager.h"
#include "RenderContext.h"
#include "GraphicsWorld.h"

#include "wolf/WolfGame.h"

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
//		return false;
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
	m_connection->setMessageHandler(boost::bind(&SimpleClient::onGameMessage, this, _1));
	if (!m_connection->connect())
	{
		r_connectionManager.removeConnection(m_connection);
		return false;
	}
	return true;
}

void SimpleClient::onGameMessage(Message* message)
{
	m_game->onHandleMessage(message);
	message->dispose();
}

void SimpleClient::onMouseEvent(tree::MouseEvent& evt)
{
	m_game->onMouseEvent(evt);
}

void SimpleClient::onKeyEvent(tree::KeyEvent& evt)
{
	m_game->onKeyEvent(evt);
}

bool SimpleClient::initGraphics()
{
	return locateResources() && loadResources();
}

bool SimpleClient::initGame()
{
	GraphicsWorld* world = m_renderContext->createGraphicsWorld();
	m_game = new WolfGame(*world);
	return m_game->init();
}

bool SimpleClient::locateResources()
{
	return m_renderContext->locateResources("resources_d.cfg");
}

bool SimpleClient::loadResources()
{
	return m_renderContext->loadAllResources();
}
