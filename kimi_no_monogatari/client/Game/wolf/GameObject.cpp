#include "pch/pch.h"

#include "GameObject.h"

GameObject::GameObject()
:m_parent(NULL),
m_dirty(true)
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

void GameObject::setPosition(float x, float y, float z)
{
	m_transform.getOrigin().setValue(x, y, z);
	m_dirty = true;
}

void GameObject::setPosition(const tree::Vec3& v)
{
	m_transform.getOrigin() = v;
	m_dirty = true;
}

void GameObject::setRotation(const tree::Quat& rot)
{
	m_transform.setRotation(rot);
	m_dirty = true;
}

void GameObject::setRotation(const tree::Mat3& rot)
{
	m_transform.getBasis() = rot;
	m_dirty = true;
}

void GameObject::setTransform(const tree::Transform& tr)
{
	m_transform = tr;
	m_dirty = true;
}

const tree::Vec3& GameObject::getPosition() const
{
	return m_transform.getOrigin();
}

const tree::Quat GameObject::getRotation() const
{
	return m_transform.getRotation();
}

const tree::Transform& GameObject::getTransform() const
{
	return m_transform;
}

void GameObject::updatePosition()
{
	if (isDirty())
	{
		if (m_parent)
			m_globalTransform = m_parent->m_globalTransform * m_transform;
		else
			m_globalTransform = m_transform;
		m_dirty = false;
	}
	for (ObjectList::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->updatePosition();
	}
}

bool GameObject::updateFromParent()
{
	if ((m_parent && m_parent->updateFromParent()) || m_dirty)
	{
		m_globalTransform = m_parent ? (m_parent->m_globalTransform * m_transform) : m_transform;
		return true;
	}
	return false;
}

void GameObject::addChild(GameObject* obj)
{
	// TODO. add graphics hirachy.
	ASSERT(!obj->getParent());
	ObjectList::iterator iter = m_children.find(obj);
	ASSERT(iter == m_children.end());
	if (iter == m_children.end())
	{
		m_children.insert(obj);
		obj->m_parent = this;
	}
}

void GameObject::removeChild(GameObject* obj)
{
	ASSERT(obj->getParent() == this);
	ObjectList::iterator iter = m_children.find(obj);
	ASSERT(iter != m_children.end());
	if (iter != m_children.end())
	{
		m_children.erase(iter);
		obj->m_parent = NULL;
	}
}
