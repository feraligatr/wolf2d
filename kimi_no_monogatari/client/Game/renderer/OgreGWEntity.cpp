#include "pch/pch.h"

#include "OgreGWEntity.h"
#include "OgreGraphicsWorld.h"
#include "OgreGraphicsHelper.h"

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

OgreGWEntity::~OgreGWEntity()
{
	while(!m_children.empty())
	{
		removeChild(*(m_children.begin()));
	}
	if (m_parent)
	{
		m_parent->removeChild(this);
	}
	Ogre::SceneManager* sm = m_gw->getOgreSceneManager();
	if (m_node)
	{
		sm->destroySceneNode(m_node);
	}
	if (m_entity)
	{
		sm->destroyEntity(m_entity);
	}
}

void OgreGWEntity::addChild(GWEntity* entity)
{
	EntityList::iterator iter = m_children.find(entity);
	ASSERT(iter == m_children.end());
	if (iter == m_children.end())
	{
		OgreGWEntity* oe = (OgreGWEntity*)entity;
		m_node->addChild(oe->m_node);
		m_children.insert(entity);
		oe->m_parent = this;
	}
}

void OgreGWEntity::removeChild(GWEntity* entity)
{
	EntityList::iterator iter = m_children.find(entity);
	ASSERT(iter != m_children.end());
	if (iter != m_children.end())
	{
		OgreGWEntity* oe = (OgreGWEntity*)entity;
		m_node->removeChild(oe->m_node);
		m_children.erase(iter);
		oe->m_parent = NULL;
	}
}

GWEntity* OgreGWEntity::getParent()
{
	return m_parent;
}

u16 OgreGWEntity::numChildren()
{
	return m_children.size();
}

void OgreGWEntity::setPosition(const tree::Vec3& pos)
{
	ASSERT(m_node);
	if (m_node)
	{
		m_node->setPosition(Vec3ToOgre(pos));
	}
}

void OgreGWEntity::setRotation(const tree::Quat& quat)
{
	ASSERT(m_node);
	if (m_node)
	{
		m_node->setOrientation(QuatToOgre(quat));
	}
}

void OgreGWEntity::setScale(const tree::Vec3& scale)
{
	ASSERT(m_node);
	if (m_node)
	{
		m_node->setScale(Vec3ToOgre(scale));
	}
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
