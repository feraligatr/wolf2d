#include "pch/pch.h"

#include "trCollisionWorld.h"


namespace tree
{

CollisionWorld::CollisionWorld(const btVector3& aabbMin, const btVector3& aabbMax)
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_overlappingPairCache = new btAxisSweep3(aabbMin, aabbMax);

	m_collisionWorld = new btCollisionWorld(m_dispatcher,m_overlappingPairCache,m_collisionConfiguration);
}

CollisionWorld::~CollisionWorld()
{
	delete m_collisionWorld;
	m_collisionWorld = 0;
	//delete broadphase
	delete m_overlappingPairCache; m_overlappingPairCache = 0;
	//delete dispatcher
	delete m_dispatcher; m_dispatcher = 0;
	delete m_collisionConfiguration; m_collisionConfiguration = 0;
}

bool CollisionWorld::addCollisionObject(CollisionObject* obj)
{
	ASSERT(m_collisionWorld);
	ASSERT(obj->m_bulletCollisionObject);
	m_collisionWorld->addCollisionObject(obj->m_bulletCollisionObject, obj->m_collisionGroup, obj->m_collisionMask);
	return true;
}

void CollisionWorld::removeCollisionObject(CollisionObject* obj)
{
	ASSERT(m_collisionWorld);
	ASSERT(obj->m_bulletCollisionObject);
	m_collisionWorld->removeCollisionObject(obj->m_bulletCollisionObject);
}

bool CollisionWorld::rayTrace(btVector3& out, const btVector3& origin, const btVector3& target, short mask)
{
	ASSERT(m_collisionWorld);

	btCollisionWorld::ClosestRayResultCallback rayCallback(origin, target);
	rayCallback.m_collisionFilterGroup = -1;
	rayCallback.m_collisionFilterMask = mask;
	m_collisionWorld->rayTest(origin, target, rayCallback);
	if (rayCallback.hasHit())
	{
		out = rayCallback.m_hitPointWorld;
		return true;
	}
	else
	{
		return false;
	}
}

void CollisionWorld::updateObjectTransform(CollisionObject* obj, const btTransform& tr)
{
	ASSERT(m_collisionWorld);
	ASSERT(obj->m_bulletCollisionObject);
	obj->_setTransform(tr);
	m_collisionWorld->updateSingleAabb(obj->m_bulletCollisionObject);
}

void CollisionWorld::performAabbCollisionDetection(CollisionCallback* callback)
{
	m_overlappingPairCache->calculateOverlappingPairs(m_collisionWorld->getDispatcher());

	btOverlappingPairCache* pairCache = m_overlappingPairCache->getOverlappingPairCache();
	for (int i = 0; i < pairCache->getNumOverlappingPairs(); ++i)
	{
		btBroadphasePair* pair = pairCache->getOverlappingPairArrayPtr() + i;
		callback->onCollide(((CollisionObject*)( ((btCollisionObject*)pair->m_pProxy0->m_clientObject)->getUserPointer() )),
			((CollisionObject*)( ((btCollisionObject*)pair->m_pProxy1->m_clientObject)->getUserPointer() ))
			);
	}

}

void CollisionWorld::performCollisionDetection(CollisionCallback* callback)
{
	m_collisionWorld->performDiscreteCollisionDetection();
	int numManifolds = m_collisionWorld->getDispatcher()->getNumManifolds();
	for (int i=0; i < numManifolds; i++)
    {
		btPersistentManifold* contactManifold = m_collisionWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
		contactManifold->refreshContactPoints(obA->getWorldTransform(),obB->getWorldTransform());

		int numContacts = contactManifold->getNumContacts();
		if (numContacts > 0)
		{
			callback->onCollide(((CollisionObject*)( obA->getUserPointer() )),
				((CollisionObject*)( obB->getUserPointer() ))
				);
		}
    }
}

}