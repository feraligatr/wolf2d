#include "pch/pch.h"
#include "OgreGWCamera.h"
#include "OgreGraphicsWorld.h"
#include "OgreGraphicsHelper.h"

OgreGWCamera::OgreGWCamera(OgreGraphicsWorld* gw, const std::string& name)
:m_gw(gw)
{
	m_ogreCamera = gw->getOgreSceneManager()->createCamera(name);
}

OgreGWCamera::~OgreGWCamera()
{
	m_gw->getOgreSceneManager()->destroyCamera(m_ogreCamera);
}

void OgreGWCamera::setPosition(const tree::Vec3& pos)
{
	ASSERT(m_ogreCamera);
	m_ogreCamera->setPosition(Vec3ToOgre(pos));
}

void OgreGWCamera::setRotation(const tree::Quat& quat)
{
	ASSERT(m_ogreCamera);
	m_ogreCamera->setOrientation(QuatToOgre(quat));
}

void OgreGWCamera::lookAt(const tree::Vec3& pos)
{
	m_ogreCamera->lookAt(Vec3ToOgre(pos));
}

void OgreGWCamera::setClipDistance(float nearDist, float farDist)
{
	m_ogreCamera->setNearClipDistance(nearDist);
	m_ogreCamera->setFarClipDistance(farDist);
}
