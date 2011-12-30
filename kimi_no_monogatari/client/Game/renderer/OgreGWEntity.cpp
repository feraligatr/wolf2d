#include "pch/pch.h"

#include "OgreGWEntity.h"

void OgreGWEntitysetPosition(const tree::Vec3& pos)
{

}

void OgreGWEntity::setRotation(const tree::Quat& quat)
{
}

void OgreGWEntity::setScale(const tree::Vec3& scale)
{
}

static u32 OgreGWEntity::generateUniqueId()
{
	static u32 generated_id = 0;
	return ++generated_id;
}

std::string OgreGWEntity::getOgreNodeName() const
{
	return std::string("_ogre_node_") + m_uniqueId;
}
std::string OgreGWEntity::getOgreEntityName() const
{
	return std::string("_ogre_entity_") + m_uniqueId;
}
