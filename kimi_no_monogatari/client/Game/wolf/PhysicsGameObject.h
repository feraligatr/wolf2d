#ifndef _PHYSICS_GAME_OBJECT_H_
#define _PHYSICS_GAME_OBJECT_H_

#include "GameObject.h"
#include "physics/PhysicsWorld.h"

class PhysicsGameObject
{
public:
	PhysicsGameObject(GameObject* obj, PhysicsWorld* pw)
		:GameObject(obj)
	{}

protected:
	PhysicsWorld* m_pw;
};


#endif /* _PHYSICS_GAME_OBJECT_H_ */
