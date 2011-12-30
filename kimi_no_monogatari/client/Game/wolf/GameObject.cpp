#include "pch/pch.h"

#include "GameObject.h"

GameObject::GameObject(GraphicsWorld* gw, PhysicsWorld* pw);
:m_gwEntity(NULL),
m_parent(NULL),
m_graphicsWorld(gw),
m_physicsWorld(pw)
{

}

GameObject::~GameObject()
{
	for (ObjectList::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		delete *iter;
	}
	if (m_parent)
	{
		m_parent->removeChild(this);
	}
}


void GameObject::addChild(GameObject* obj)
{
	// TODO. add graphics hirachy.
	ASSERT(!obj->getParent());
	ObjectList::iterator iter = find(m_children.begin(), m_children.end(), obj);
	ASSERT(iter == m_children.end());
	if (iter == m_children.end())
	{
		m_children.push_back(obj);
		obj->m_parent = this;
	}
}

void GameObject::removeChild(GameObject* obj)
{
	ASSERT(obj->getParent() == this);
	ObjectList::iterator iter = find(m_children.begin(), m_children.end(), obj);
	ASSERT(iter != m_children.end());
	if (iter != m_children.end())
	{
		m_children.erase(iter);
		obj->m_parent = NULL;
	}
}
