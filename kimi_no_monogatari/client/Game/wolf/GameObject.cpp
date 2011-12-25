#include "pch/pch.h"

#include "GameObject.h"

GameObject::GameObject(GameObject* parent)
:m_gwEntity(NULL),
m_parent(NULL)
{
	if (parent)
	{
		parent->addChild(this);
	}
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
