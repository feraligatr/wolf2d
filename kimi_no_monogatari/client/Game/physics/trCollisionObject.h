#ifndef _TR_COLLISION_OBJECT_H_
#define _TR_COLLISION_OBJECT_H_

#include "trCollisionShape.h"

class btCollisionObject;
class btCollisionShape;

namespace tree
{

enum COLLISION_FILTER
{
	STATIC_FILTER = 1,
	DYNAMIC_FILTER = 2,
	ALL_FILTER = -1,
};

class CollisionObject
{
public:
	CollisionObject(CollisionShape* shape, const btTransform& tr, short collisionGroup = ALL_FILTER, short collisionMask = ALL_FILTER);
	virtual ~CollisionObject();

private:
	friend class CollisionWorld;
	void _clearBulletData();
	void _initBulletData(CollisionShape* shape);
	void _setTransform(const btTransform& tr);

	btCollisionShape* _getSimpleBTShape(CollisionShape* shape);
private:
	
	btCollisionObject* m_bulletCollisionObject;

	btTransform m_transform;

	short m_collisionGroup;
	short m_collisionMask;
	
};

}


#endif