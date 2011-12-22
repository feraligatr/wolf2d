#include "pch/pch.h"

#include "OgreGraphicsWorld.h"

using namespace Ogre;

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

bool OgreGraphicsWorld::locateResources(const char* cfgfile)
{
	// load resource paths from config file
	try
	{
			Ogre::ConfigFile cf;
			cf.load(cfgfile);

			Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
			Ogre::String sec, type, arch;

			// go through all specified resource groups
			while (seci.hasMoreElements())
			{
				sec = seci.peekNextKey();
				Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
				Ogre::ConfigFile::SettingsMultiMap::iterator i;

				// go through all resource paths
				for (i = settings->begin(); i != settings->end(); i++)
				{
					type = i->first;
					arch = i->second;

					#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
                    // OS X does not set the working directory relative to the app,
                    // In order to make things portable on OS X we need to provide
                    // the loading with it's own bundle path location
					if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
						arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
					#endif
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
				}
			}
	}
	catch (Ogre::Exception e)
	{
		return false;
	}
	return true;
}

bool OgreGraphicsWorld::loadAllResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	return true;
}
