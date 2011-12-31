#include "pch/pch.h"

#include "WolfGameObject.h"

WolfGameObject::WolfGameObject(GraphicsWorld* gw, tree::PhysicsWorld* pw)
:m_graphicsWorld(gw),
m_physicsWorld(pw),
m_gwEntity(NULL)
{

}

void WolfGameObject::createGraphicsEntity(const std::string& meshName, const std::string& matName)
{
	ASSERT(!m_gwEntity);
	ASSERT(m_graphicsWorld);
	m_graphicsWorld->createEntity(meshName, matName);
}


