#include "pch/pch.h"

#include "OgreGraphicsWorld.h"
#include "OgreGWEntity.h"

using namespace Ogre;

OgreGraphicsWorld::OgreGraphicsWorld(Ogre::Root* root, Ogre::RenderWindow* renderWindow)
	:m_ogreRoot(root),
	 m_renderWindow(renderWindow),
	 m_rootEntity(NULL)
{

}

OgreGraphicsWorld::~OgreGraphicsWorld()
{

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

//bool OgreGraphicsWorld::start()
//{
//	// fake a scene start, In fact. the world setup should done by Game logic.
//	
//	Ogre::SceneType scene_manager_type = Ogre::ST_EXTERIOR_CLOSE;
//
//	m_sceneManager = m_root->createSceneManager( scene_manager_type );
//	m_sceneManager->setAmbientLight( Ogre::ColourValue(1,1,1) );
//
//	m_camera = m_sceneManager->createCamera( "sample_cam" );
//	m_camera->setPosition( Ogre::Vector3(0,1,0) );
//	m_camera->lookAt( Ogre::Vector3(0,0,0) );
//	m_camera->setNearClipDistance( 1.0 );
//
//	m_viewport = m_renderWindow->addViewport( m_camera );
//	m_viewport->setBackgroundColour( Ogre::ColourValue( 0,0,0 ) );
//	return true;
//}

