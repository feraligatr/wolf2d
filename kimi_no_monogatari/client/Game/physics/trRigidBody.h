#ifndef _TR_RIGID_BODY_H_
#define _TR_RIGID_BODY_H_

#include "trCollisionShape.h"

class btRigidBody;

namespace tree
{

class RigidBodyInfo
{
public:
	enum COLLISION_FILTER
	{
		STATIC_FILTER = 1,
		DYNAMIC_FILTER = 2,
		ALL_FILTER = -1,
	};

	enum MISC_INFO
	{
		IS_KINEMATICS = 1,
		SET_LOCAL_INERTIA = 2,
		NEED_CCD = 4,
	};

	RigidBodyInfo()
		:m_mass(0.),
		m_localInertia(0, 0, 0),
		m_linearPos(0, 0, 0),
		m_linearVelocity(0, 0, 0),
		m_rotation(0, 0, 0, 1),
		m_angularVelocity(0, 0, 0),
		m_linearDamping(0.), 
		m_angularDamping(0.), 
		m_friction(0.5), 
		m_resititution(0.),
		m_collisionMask(0),
		m_collisionGroup(0),
		m_angularSleepingThreshold(1.0f),
		m_linearSleepingThreshold(0.8f),
		m_additionalDamping(false),
		m_additionalDampingFactor(btScalar(0.005)),
		m_additionalLinearDampingThresholdSqr(btScalar(0.01)),
		m_additionalAngularDampingThresholdSqr(btScalar(0.01)),
		m_additionalAngularDampingFactor(btScalar(0.01)),
		m_miscFlag(0)
	{
		
	}
	
	// additional damping.
	bool m_additionalDamping;
	btScalar m_additionalDampingFactor;
	btScalar m_additionalLinearDampingThresholdSqr;
	btScalar m_additionalAngularDampingThresholdSqr;
	btScalar m_additionalAngularDampingFactor;

	btScalar m_mass;
	btVector3 m_localInertia;
	
	btVector3 m_linearPos;
	btVector3 m_linearVelocity;

	btQuaternion m_rotation;
	btVector3 m_angularVelocity;

	btScalar m_linearDamping;
	btScalar m_angularDamping;

	btScalar m_friction;
	btScalar m_resititution;

	btScalar m_linearSleepingThreshold;
	btScalar m_angularSleepingThreshold;

	short m_collisionMask;
	short m_collisionGroup;

	int m_miscFlag;

	inline int isKinematics() const {
		return m_miscFlag & IS_KINEMATICS;
	}

	void setKinematic(bool flag)
	{
		if (flag)
			m_miscFlag |= IS_KINEMATICS;
		else
			m_miscFlag &= (~IS_KINEMATICS);
	}

	inline void setNeedInertial(bool flag)
	{
		if (flag)
			m_miscFlag |= SET_LOCAL_INERTIA;
		else
			m_miscFlag &= (~SET_LOCAL_INERTIA);
	}

	inline int needSetLocalInertia() const {
		return m_miscFlag & SET_LOCAL_INERTIA;
	}

	inline void setNeedCCD(bool flag)
	{
		if (flag)
			m_miscFlag |= NEED_CCD;
		else
			m_miscFlag &= (~NEED_CCD);
	}

	inline int needCCD() const {
		return m_miscFlag & NEED_CCD;
	}
};

class RigidBody
{
public:
	RigidBody(const RigidBodyInfo& info, CollisionShape* shape, const btVector3& pivotOffset = btVector3(0, 0, 0));
	~RigidBody();

	void getPivotTransform(btTransform& t);
	void getTransform(btTransform& t);
	void setTransform(const btTransform& tr);

	btVector3 getVelocity(const btVector3& pos);
	const btVector3& getLinearVelocity();
	const btVector3& getAngularVelocity();

	void applyImpulse(const btVector3& impulse, const btVector3& pos);
	void applyCentralImpulse(const btVector3& impulse);

	void updateKinematicsMotion(const btScalar& timeStep);


	inline btRigidBody* getBulletBody() {
		return m_bulletBody;
	}

	const RigidBodyInfo& getInfo() const {
		return m_info;
	}

	void setUserData(void* userData) {
		m_userData = userData;
	}
	void* getUserData() {
		return m_userData;
	}

	CollisionShape* getCollisionShape() {
		return m_shape;
	}

	friend class MyMotionState;
	
private:
	void initBulletData();
	void clearBulletData();

	btRigidBody* m_bulletBody;
	CollisionShape* m_shape;

	RigidBodyInfo m_info;

	btTransform m_pivotTransform;
	btVector3 m_pivotOffset;

	void* m_userData;

};

}

#endif