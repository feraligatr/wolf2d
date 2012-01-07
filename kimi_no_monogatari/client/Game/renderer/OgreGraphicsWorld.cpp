#include "pch/pch.h"

#include "OgreGraphicsWorld.h"
#include "OgreGWEntity.h"
#include "OgreGWCamera.h"

using namespace Ogre;

OgreGraphicsWorld::OgreGraphicsWorld(Ogre::Root* root, Ogre::RenderWindow* renderWindow, int width, int height)
	:m_ogreRoot(root),
	 m_renderWindow(renderWindow),
	 m_rootEntity(NULL),
	 m_viewport(NULL),
	 m_activeCamera(NULL),
	 m_width(width),
	 m_height(height)
{
	_createOgreSceneManager();
}

OgreGraphicsWorld::~OgreGraphicsWorld()
{
	for (EntityList::iterator iter = m_allEntitys.begin(); iter != m_allEntitys.end(); ++iter)
	{
		delete (*iter);
	}
	for (CameraList::iterator iter = m_allCameras.begin(); iter != m_allCameras.end(); ++iter)
	{
		delete (*iter);
	}
}

void OgreGraphicsWorld::_createOgreSceneManager()
{
	m_sceneManager = m_ogreRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE);
}

GWEntity* OgreGraphicsWorld::getRoot()
{
	return m_rootEntity;
}

void OgreGraphicsWorld::setSkyBox(const std::string& skybox_rs, float distance)
{
	m_sceneManager->setSkyBox(true, skybox_rs, distance);
}

void OgreGraphicsWorld::setAmbientLight(float r, float g, float b)
{
	m_sceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
}

GWEntity* OgreGraphicsWorld::createEntity(const std::string& meshName, const std::string& matName)
{
	OgreGWEntity* entity = new OgreGWEntity(this, meshName, matName);
	m_allEntitys.insert(entity);
	return entity;
}

void OgreGraphicsWorld::destroyEntity(GWEntity* entity)
{
	ASSERT(!entity->getParent());
	ASSERT(entity->numChildren() == 0);
	m_allEntitys.erase((OgreGWEntity*)entity);
	delete entity;
}

GWCamera* OgreGraphicsWorld::createCamera(const std::string& name)
{
	OgreGWCamera* camera = new OgreGWCamera(this, name);
	camera->getOgreCamera()->setAspectRatio((float)m_width / m_height);
	m_allCameras.insert(camera);
	if (!m_activeCamera)
	{
		setActiveCamera(camera);
	}
	return camera;
}

void OgreGraphicsWorld::setActiveCamera(GWCamera* camera)
{
	if (m_activeCamera)
	{
		ASSERT(m_viewport);
		m_renderWindow->removeAllViewports();
	}
	OgreGWCamera* cam = (OgreGWCamera*)camera;
	m_viewport = m_renderWindow->addViewport(cam->getOgreCamera());
	m_viewport->setBackgroundColour(Ogre::ColourValue( 0.5,0.5,0.5 ));
	m_activeCamera = cam;
}

void OgreGraphicsWorld::resize(int width, int height)
{
	m_width = width;
	m_height = height;
	for (CameraList::iterator iter = m_allCameras.begin(); iter != m_allCameras.end(); ++iter)
	{
		((OgreGWCamera*)(*iter))->getOgreCamera()->setAspectRatio((float)width/height);
	}
}
