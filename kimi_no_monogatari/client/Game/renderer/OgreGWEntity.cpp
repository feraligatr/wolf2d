#include "pch/pch.h"

#include "OgreGWEntity.h"
#include "OgreGraphicsWorld.h"

OgreGWEntity::OgreGWEntity(OgreGraphicsWorld* gw, const std::string& meshName, const std::string& matName)
:m_gw(gw)
,m_node(NULL)
,m_entity(NULL)
,m_parent(NULL)
{
	m_uniqueId = generateUniqueId();
	Ogre::SceneManager* sm = m_gw->getOgreSceneManager();
	m_node = sm->createSceneNode(getOgreNodeName());
	if (!meshName.empty())
	{
		m_entity = sm->createEntity(getOgreEntityName(), meshName);
		if (!matName.empty())
		{
			m_entity->setMaterialName(matName);
		}
	}
}

void OgreGWEntity::setPosition(const tree::Vec3& pos)
{
	ASSERT(m_node);
	if (m_node)
	{
	}
}

void OgreGWEntity::setRotation(const tree::Quat& quat)
{
}

void OgreGWEntity::setScale(const tree::Vec3& scale)
{
}

u32 OgreGWEntity::generateUniqueId()
{
	static u32 generated_id = 0;
	return ++generated_id;
}

std::string OgreGWEntity::getOgreNodeName() const
{
	std::string _ret = std::string("_ogre_node_");
	_ret += m_uniqueId;
	return _ret;
}
std::string OgreGWEntity::getOgreEntityName() const
{
	std::string _ret = std::string("_ogre_entity_");
	_ret += m_uniqueId;
	return _ret;
}
