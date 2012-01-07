#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

// 2. design GraphicsWorld interface.
// 3. GraphicsEntity has tree hierachy structure.
// 4. GameObject has their own tree hierachy structure. And only hierachy structure.
// then WolfGameObject decide how to handle the physics and graphics node.

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

// position
	void setPosition(float x, float y, float z);
	void setPosition(const tree::Vec3& v);

	void setRotation(const tree::Quat& rot);
	void setRotation(const tree::Mat3& rot);

	void setTransform(const tree::Transform& tr);

	const tree::Vec3& getPosition() const;
	const tree::Quat getRotation() const;
	const tree::Transform& getTransform() const;

	// update this and all sub objects.
	void update(float dt);

// structure
	void detach();
	void addChild(GameObject* obj);
	void removeChild(GameObject* obj);
	// update position from root. this function should be called on root.
	void updatePosition();
	// update the final position of the object. will update all dirty parent position.
	// just update the final position of the parent, but not update dirty.
	// so no essential requirement, do not call it.
	// return value. whether the parent is dirty.
	bool updateFromParent();
	typedef std::set<GameObject*> ObjectList;

protected:
	virtual void updateInternal(float dt);

	inline GameObject* getParent() {
		return m_parent;
	}

	inline bool isDirty() const {
		return m_dirty;
	}

protected:
	GameObject* m_parent;
	ObjectList m_children;

	bool m_dirty;
	// local.
	tree::Transform m_transform;
	// global
	tree::Transform m_globalTransform;

};

#endif /* _GAME_OBJECT_H_ */
