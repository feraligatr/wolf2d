#ifndef _TR_PHYSICS_WORLD_H_
#define _TR_PHYSICS_WORLD_H_

#include "trRigidBody.h"

class btCollisionConfiguration;
class btDispatcher;
class btBroadphaseInterface;
class btDiscreteDynamicsWorld;
class btSequentialImpulseConstraintSolver;

namespace tree
{

class PhysicsConfig
{
public:
	//enum STATE_FLAG 
	//{
	//	NEED_HANDlE_COLLISION = 1,
	//};
	
public:
	PhysicsConfig()
		:m_proxyNum(1024),
		m_aabbMin(-1000, -1000, -1000), 
		m_aabbMax(1000, 1000, 1000), 
		m_maxPersistentManifoldPoolSize(256),
		m_maxCollisionAlgorithmPoolSize(256),
		m_maxSubSteps(3),
		m_fixedTimeStep(btScalar(0.016)),
		m_g(0, 0, btScalar(-9.8)),
		m_needGhost(true)
	{

	}
	
	int m_maxSubSteps;
	btScalar m_fixedTimeStep;

	btVector3 m_g;
	btVector3 m_aabbMin;
	btVector3 m_aabbMax;

	bool m_needGhost;
	unsigned short m_proxyNum;

	short m_maxPersistentManifoldPoolSize;
	short m_maxCollisionAlgorithmPoolSize;
};

class PhysicsWorld
{
public:
	PhysicsWorld(const PhysicsConfig& config);
	~PhysicsWorld();

	bool update(const btScalar& dt);

	bool addBody(RigidBody* body);
	void removeBody(RigidBody* body);

	bool rayTrace(btVector3& out, const btVector3& origin, const btVector3& target, short mask);

	void debugDraw();

	inline btDiscreteDynamicsWorld* _getBulletWorld() 
	{
		return m_dynamicsWorld;
	}

private:
	PhysicsConfig m_config;
	// bullet 
	btCollisionConfiguration* m_collisionConfiguration;
	btDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_constraintSolver;

	btDiscreteDynamicsWorld* m_dynamicsWorld;

};

}

#endif