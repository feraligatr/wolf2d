#ifndef _TR_COLLISION_WORLD_H_
#define _TR_COLLISION_WORLD_H_

#include "trCollisionObject.h"

class btCollisionConfiguration;
class btDispatcher;
class btBroadphaseInterface;
class btCollisionWorld;

namespace tree
{

class CollisionCallback
{
public:
	virtual ~CollisionCallback() {}
	virtual void onCollide(CollisionObject* a, CollisionObject* b) = 0;
};

class CollisionWorld
{
public:
	CollisionWorld(const btVector3& aabbMin = btVector3(-1000, -1000, -1000), const btVector3& aabbMax = btVector3(1000, 1000, 1000));
	~CollisionWorld();

	bool addCollisionObject(CollisionObject* obj);
	void removeCollisionObject(CollisionObject* obj);

	void updateObjectTransform(CollisionObject* obj, const btTransform& tr);

	// only return the nearest point.
	bool rayTrace(btVector3& out, const btVector3& origin, const btVector3& target, short mask);
	void performAabbCollisionDetection(CollisionCallback* callback);
	void performCollisionDetection(CollisionCallback* callback);

private:
	// bullet 
	btCollisionConfiguration* m_collisionConfiguration;
	btDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;

	btCollisionWorld* m_collisionWorld;
	
};

}

#endif