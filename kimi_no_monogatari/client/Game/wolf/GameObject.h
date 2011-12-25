#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "renderer/Graphics.h"

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
	GameObject m_parent;
	ObjectList m_children;

	// TODO: decide the time to create the graphics entity.
	// link to Graphics.
	GWEntity* m_gwEntity;
	// TODO: add phycis entity to do collisions.
	// PhysicsObject : public GameObject.
	// PhysicsObject(PhysicsWorld* world);

};

#endif /* _GAME_OBJECT_H_ */
