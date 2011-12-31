#ifndef _WOLF_GAME_OBJECT_H_
#define _WOLF_GAME_OBJECT_H_

#include "GameObject.h"

#include "renderer/Graphics.h"
#include "physics/trPhysics.h"

class WolfGameObject : public GameObject
{
public:
	WolfGameObject(GraphicsWorld* gw, tree::PhysicsWorld* pw);

protected:
	// helper function. for create entity easier.
	void createGraphicsEntity(const std::string& meshName = "", const std::string& matName = "");

protected:
	GraphicsWorld* m_graphicsWorld;
	tree::PhysicsWorld* m_physicsWorld;

	// the gwEntity can be null. and the gwEntity will be global position. and create from the same root object.
	GWEntity* m_gwEntity;
};

#endif /* _WOLF_GAME_OBJECT_H_ */

