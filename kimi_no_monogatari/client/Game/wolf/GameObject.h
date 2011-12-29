#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "renderer/Graphics.h"
#include "physics/Physics.h"

class GameObject
{
public:
	GameObject(GameObject* parent);
	virtual ~GameObject();
	addChild(GameObject* obj);
	removeChild(GameObject* obj);

	typedef std::vector<GameObject*> ObjectList;

protected:
	GameObject* getParent() {
		return m_parent;
	}

protected:
	GameObject* m_parent;
	ObjectList m_children;

	GraphicsWorld* m_graphicsWorld;
	PhysicsWorld* m_physicsWorld;
	// TODO: decide the time to create the graphics entity.
	// link to Graphics.
	// m_gwEntity can not be null. because the Graphics World 
	// need the object hierachy.
	GWEntity* m_gwEntity;

};

#endif /* _GAME_OBJECT_H_ */
