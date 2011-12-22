#include "pch/pch.h"

#include "SimpleClient.h"

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
	return true;
}
