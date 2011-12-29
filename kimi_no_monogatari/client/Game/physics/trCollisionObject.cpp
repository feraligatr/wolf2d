#include "pch/pch.h"

#include "trCollisionObject.h"

namespace tree
{

CollisionObject::CollisionObject(CollisionShape* shape, const btTransform& tr, short collisionGroup, short collisionMask)
:m_bulletCollisionObject(0),
m_collisionGroup(collisionGroup),
m_collisionMask(collisionMask),
m_transform(tr)
{
	_initBulletData(shape);
}

CollisionObject::~CollisionObject()
{
	_clearBulletData();
}

void CollisionObject::_initBulletData(CollisionShape* shape)
{
	shape->initBulletShape();
	m_bulletCollisionObject = new btCollisionObject();
	m_bulletCollisionObject->setCollisionShape(shape->m_bulletShape);
	m_bulletCollisionObject->setUserPointer(this);
	m_bulletCollisionObject->setCollisionFlags(0);
}

void CollisionObject::_clearBulletData()
{
	delete m_bulletCollisionObject;
	m_bulletCollisionObject = 0;
}


void CollisionObject::_setTransform(const btTransform& tr)
{
	m_transform = tr;
	if (m_bulletCollisionObject)
	{
		m_bulletCollisionObject->setWorldTransform(tr);
	}
}

}