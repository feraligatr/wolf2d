#include "pch/pch.h"

#include "OgreGraphicsWorld.h"

OgreGraphicsWorld::OgreGraphicsWorld(Ogre::Root* root, Ogre::RenderWindow* renderWindow)
	:m_root(root),
	 m_renderWindow(renderWindow)
{
	
}

bool OgreGraphicsWorld::start()
{
	// fake a scene start, In fact. the world setup should done by Game logic.
	
	Ogre::SceneType scene_manager_type = Ogre::ST_EXTERIOR_CLOSE;

	m_sceneManager = m_root->createSceneManager( scene_manager_type );
	m_sceneManager->setAmbientLight( Ogre::ColourValue(1,1,1) );

	m_camera = m_sceneManager->createCamera( "sample_cam" );
	m_camera->setPosition( Ogre::Vector3(0,1,0) );
	m_camera->lookAt( Ogre::Vector3(0,0,0) );
	m_camera->setNearClipDistance( 1.0 );

	m_viewport = m_renderWindow->addViewport( m_camera );
	m_viewport->setBackgroundColour( Ogre::ColourValue( 0,0,0 ) );
	return true;
}
