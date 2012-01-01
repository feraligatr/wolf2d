#include "pch/pch.h"
#include "trRigidBody.h"

namespace tree
{

class MyMotionState : public btMotionState {
public:
	MyMotionState(RigidBody* e) {
		m_e = e;
	}

	virtual void getWorldTransform(btTransform &worldTrans) const {
		assert(m_e);
		if (m_e)
			worldTrans = m_e->m_pivotTransform;
	}
	virtual void setWorldTransform(const btTransform& worldTrans) {
		assert(m_e);
		if (m_e)
			m_e->m_pivotTransform = worldTrans;
	}

protected:
	RigidBody* m_e;
};


RigidBody::RigidBody(const RigidBodyInfo& info, CollisionShape* shape, const btVector3& pivotOffset)
:m_pivotOffset(pivotOffset),
m_shape(shape),
m_info(info),
m_userData(0)
{
	m_pivotTransform.getBasis().setRotation(info.m_rotation);
	btVector3 pos = info.m_linearPos;
	m_pivotTransform.getOrigin() = (pos + m_pivotTransform.getBasis() * m_pivotOffset);

	initBulletData();
}

RigidBody::~RigidBody()
{
	clearBulletData();
}

void RigidBody::initBulletData()
{
	m_shape->initBulletShape();
	ASSERT(m_shape->m_bulletShape);
	btScalar mass(m_info.m_mass);
	bool isDynamic = (mass != 0.f);
	
	// calc inertia.
	btVector3 localInertia(0.,0.,0.);
	if (isDynamic)
	{
		if (m_info.needSetLocalInertia())
		{
			ASSERT(m_info.m_localInertia.x() >= 0 && m_info.m_localInertia.y() >= 0 && m_info.m_localInertia.z() >= 0);
			localInertia = m_info.m_localInertia;
		}
		else
		{
			m_shape->m_bulletShape->calculateLocalInertia(mass, localInertia);
		}
	}

	// setup motion state.
	btMotionState* motionState = 0;
	motionState = new MyMotionState(this);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motionState,m_shape->m_bulletShape,localInertia);
	rbInfo.m_linearDamping = m_info.m_linearDamping;
	rbInfo.m_angularDamping = m_info.m_angularDamping;
	rbInfo.m_friction = m_info.m_friction;
	rbInfo.m_restitution = m_info.m_resititution;
	rbInfo.m_linearSleepingThreshold = m_info.m_linearSleepingThreshold;
	rbInfo.m_angularSleepingThreshold = m_info.m_angularSleepingThreshold;

	rbInfo.m_additionalDamping = m_info.m_additionalDamping;
	rbInfo.m_additionalDampingFactor = m_info.m_additionalDampingFactor;
	rbInfo.m_additionalLinearDampingThresholdSqr = m_info.m_additionalLinearDampingThresholdSqr;
	rbInfo.m_additionalAngularDampingThresholdSqr = m_info.m_additionalAngularDampingThresholdSqr;
	rbInfo.m_additionalAngularDampingFactor = m_info.m_additionalAngularDampingFactor;

	m_bulletBody = new btRigidBody(rbInfo);
	m_bulletBody->setUserPointer(this);

	if (isDynamic)
	{
		m_bulletBody->setLinearVelocity(m_info.m_linearVelocity);
		m_bulletBody->setAngularVelocity(m_info.m_angularVelocity);
	}
	else if (m_info.isKinematics())
	{
		m_bulletBody->setCollisionFlags(m_bulletBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	}

	if (m_info.m_collisionGroup == 0 && m_info.m_collisionMask == 0)
	{
		if (isDynamic)
		{
			m_info.m_collisionGroup = RigidBodyInfo::DYNAMIC_FILTER;
			m_info.m_collisionMask = RigidBodyInfo::ALL_FILTER;
		}
		else
		{
			m_info.m_collisionGroup = RigidBodyInfo::STATIC_FILTER;
			m_info.m_collisionMask = (RigidBodyInfo::ALL_FILTER) & (~(RigidBodyInfo::STATIC_FILTER));
		}
	}

	// ccd
	if (m_info.needCCD())
	{
		btTransform tr = btTransform::getIdentity();
		btVector3 aabbMin, aabbMax;
		m_shape->m_bulletShape->getAabb(tr, aabbMin, aabbMax);
		btVector3 dist = aabbMax - aabbMin;
		btScalar min_dist = dist[dist.minAxis()] * 0.5f;
		m_bulletBody->setCcdMotionThreshold(min_dist * 0.5f);
		m_bulletBody->setCcdSweptSphereRadius(min_dist * 0.2f);
	}
}

void RigidBody::clearBulletData()
{
	if (m_bulletBody)
	{
		delete m_bulletBody->getMotionState();
	}
	delete m_bulletBody;
	m_bulletBody = 0;
}

void RigidBody::getPivotTransform(btTransform& t)
{
	t = m_pivotTransform;
}

void RigidBody::getTransform(btTransform& t)
{
	btVector3 pos = m_pivotTransform.getOrigin();
	pos = pos - m_pivotTransform.getBasis() * m_pivotOffset;
	t.getBasis() = m_pivotTransform.getBasis();
	t.getOrigin() = pos;
}

void RigidBody::setTransform(const btTransform& t)
{
	m_pivotTransform.getBasis() = t.getBasis();
	btVector3 pos(t.getOrigin());
	m_pivotTransform.getOrigin() = (pos + m_pivotTransform.getBasis() * m_pivotOffset);
}

const btVector3& RigidBody::getLinearVelocity()
{
	assert(m_bulletBody);
	return m_bulletBody->getLinearVelocity();
}

const btVector3& RigidBody::getAngularVelocity()
{
	assert(m_bulletBody);
	return m_bulletBody->getAngularVelocity();
}

btVector3 RigidBody::getVelocity(const btVector3& pos)
{
	assert(m_bulletBody);
	return m_bulletBody->getVelocityInLocalPoint(pos - m_bulletBody->getCenterOfMassPosition());
}

void RigidBody::applyImpulse(const btVector3& impulse, const btVector3& pos)
{
	assert(m_bulletBody);
	m_bulletBody->applyImpulse(impulse, pos - m_bulletBody->getCenterOfMassPosition());
}

void RigidBody::applyCentralImpulse(const btVector3& impulse)
{
	assert(m_bulletBody);
	m_bulletBody->applyCentralImpulse(impulse);
}

}