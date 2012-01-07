#ifndef _OGRE_GW_ENTITY_H_
#define _OGRE_GW_ENTITY_H_

#include "GWEntity.h"

class OgreGraphicsWorld;

class OgreGWEntity : public GWEntity
{
public:
	OgreGWEntity(OgreGraphicsWorld* gw, const std::string& meshName, const std::string& matName);
	virtual ~OgreGWEntity();

	virtual void setPosition(const tree::Vec3& pos);
	virtual void setRotation(const tree::Quat& quat);
	virtual void setScale(const tree::Vec3& scale);

	// hierarchy.
	virtual void addChild(GWEntity* entity);
	virtual void removeChild(GWEntity* entity);
	virtual GWEntity* getParent();
	virtual u16 numChildren();

private:
	static u32 generateUniqueId();
	std::string getOgreNodeName() const;
	std::string getOgreEntityName() const;

private:
	u32 m_uniqueId;
	Ogre::SceneNode* m_node;
	Ogre::Entity* m_entity;
	OgreGraphicsWorld* m_gw;

	OgreGWEntity* m_parent;
	typedef std::set<GWEntity*> EntityList;
	EntityList m_children;

};

#endif /* _OGRE_GW_ENTITY_H_ */
