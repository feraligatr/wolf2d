#include "pch/pch.h"
#include "trPhysicsWorld.h"

namespace tree
{

PhysicsWorld::PhysicsWorld(const PhysicsConfig& config)
:m_config(config)
{
	btDefaultCollisionConstructionInfo info;
	info.m_defaultMaxCollisionAlgorithmPoolSize = config.m_maxPersistentManifoldPoolSize;
	info.m_defaultMaxCollisionAlgorithmPoolSize = config.m_maxCollisionAlgorithmPoolSize;
	m_collisionConfiguration = new btDefaultCollisionConfiguration(info);
//	((btDefaultCollisionConfiguration*)m_collisionConfiguration)->setConvexConvexMultipointIterations(3, 3);

	
	m_overlappingPairCache = new btAxisSweep3(config.m_aabbMin, config.m_aabbMax, config.m_proxyNum);
	
	//if (config.m_needGhost)
	//{
	//	m_dispatcher = new IgnoreGhostDispatcher(m_collisionConfiguration);
	//}
	//else
	//{
		m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
//	}
	m_constraintSolver = new btSequentialImpulseConstraintSolver();


	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_constraintSolver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(config.m_g);

	//m_dynamicsWorld->setInternalTickCallback(singleSimulationFinish, this);
	//if (m_globalInfo.m_stateFlag & lGlobalPhysicsInfo::NEED_HANDlE_COLLISION)
	//{
	//	gContactProcessedCallback = myCallback;
	//}
}

PhysicsWorld::~PhysicsWorld()
{
	if (!m_dynamicsWorld) return;
	int i;
	for (i=m_dynamicsWorld->getNumConstraints()-1; i>=0 ;i--)
	{
		btTypedConstraint* constraint = m_dynamicsWorld->getConstraint(i);
		m_dynamicsWorld->removeConstraint(constraint);
	}
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		m_dynamicsWorld->removeCollisionObject( obj );
	}
	delete m_dynamicsWorld;
	m_dynamicsWorld = 0;
	delete m_constraintSolver;
	m_constraintSolver = 0;
	delete m_dispatcher;
	m_dispatcher = 0;
	delete m_overlappingPairCache;
	m_overlappingPairCache = 0;
	delete m_collisionConfiguration;
	m_collisionConfiguration = 0;
}

bool PhysicsWorld::update(const btScalar& dt)
{
	ASSERT(m_dynamicsWorld);
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(dt, m_config.m_maxSubSteps, m_config.m_fixedTimeStep);
		return true;
	}
	else
	{
		return false;
	}
}

bool PhysicsWorld::rayTrace(btVector3& out, const btVector3& origin, const btVector3& target, short mask)
{
	ASSERT(m_dynamicsWorld);

	btCollisionWorld::ClosestRayResultCallback rayCallback(origin, target);
	rayCallback.m_collisionFilterGroup = -1;
	rayCallback.m_collisionFilterMask = mask;
	m_dynamicsWorld->rayTest(origin, target, rayCallback);
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

bool PhysicsWorld::addBody(RigidBody* body)
{
	ASSERT(m_dynamicsWorld);
	ASSERT(body);
	ASSERT(body->getBulletBody());

	m_dynamicsWorld->addRigidBody(body->getBulletBody(), body->getInfo().m_collisionGroup, body->getInfo().m_collisionMask);
	return true;
}

void PhysicsWorld::removeBody(RigidBody* body)
{
	ASSERT(m_dynamicsWorld);
	ASSERT(body);
	ASSERT(body->getBulletBody());
	m_dynamicsWorld->removeRigidBody(body->getBulletBody());
}

void PhysicsWorld::debugDraw()
{
	m_dynamicsWorld->debugDrawWorld();
}
}