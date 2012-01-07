#include "pch/pch.h"

#include "OgreRenderContext.h"
#include "OgreGraphicsWorld.h"
#include "Ogre.h"

#include <QString>

OgreRenderContext::OgreRenderContext()
{

}

OgreRenderContext::~OgreRenderContext()
{
	exit();
}

GraphicsWorld* OgreRenderContext::createGraphicsWorld()
{
	GraphicsWorld* world = NULL;
	try
	{
		world = new OgreGraphicsWorld(m_root, m_renderWindow, m_width, m_height);
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::createGraphicsWorld exception" << e.what();
		return NULL;
	}
	m_worlds.insert(world);
	return world;
}

void OgreRenderContext::destroyGraphicsWorld(GraphicsWorld* world)
{
	try
	{
		m_worlds.erase(world);
		delete world;
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::destroyGraphicsWorld exception" << e.what();
	}
}


void OgreRenderContext::resize(int width, int height)
{
	m_width = width;
	m_height = height;
	try
	{
		for (GraphicsWorldList::iterator iter = m_worlds.begin(); iter != m_worlds.end(); ++iter)
		{
			((OgreGraphicsWorld*)(*iter))->resize(width, height);
		}
		m_renderWindow->reposition(0, 0);
		m_renderWindow->resize(width, height);
//		m_renderWindow->windowMovedOrResized();
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::resize exception" << e.what();
	}
}

bool OgreRenderContext::start(int windowId, int width, int height)
{
	m_width = width;
	m_height = height;
	try
	{
		initOgre("plugins_d.cfg", "ogre_config.cfg", "output.log", width, height);
		createRenderWindow(windowId, width, height);
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::start: exception" << e.what();
	}
	return true;
}

void OgreRenderContext::exit()
{
	try
	{
		for (GraphicsWorldList::iterator iter = m_worlds.begin(); iter != m_worlds.end(); ++iter)
		{
			delete *iter;
		}
		m_worlds.clear();

		if (m_root)
		{
			m_root->shutdown();
			delete m_root;
			m_root = NULL;
		}
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::exit: exception" << e.what();
	}
}

void OgreRenderContext::render()
{
	m_root->renderOneFrame();
}

void OgreRenderContext::createRenderWindow(int windowId, int width, int height)
{
	try
	{
		Ogre::String winHandle;
	#ifdef WIN32
		// Windows code
		winHandle += Ogre::StringConverter::toString((unsigned long)windowId);
	#else
		// Unix code
		QX11Info info = x11Info();
		winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
		winHandle += ":";
		winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
		winHandle += ":";
		winHandle += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));
	#endif
		Ogre::NameValuePairList params;
		params["parentWindowHandle"] = winHandle;

		m_renderWindow = m_root->createRenderWindow( "QOgreWidget_RenderWindow",
			width,
			height,
			false,
			&params );
		m_renderWindow->setActive(true);
		m_renderWindow->reposition(0, 0);
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::createRenderWindow exception " << e.what();
	}
}

WId OgreRenderContext::getWindowId() const
{
	WId ogreWinId = 0x0;
	m_renderWindow->getCustomAttribute( "WINDOW", &ogreWinId );
	ASSERT(ogreWinId != 0);
	return ogreWinId;
}

void OgreRenderContext::initOgre(const std::string& plugins_file,
		const std::string& ogre_cfg_file,
		const std::string& ogre_log,
		int width, int height)
{
	try
	{
		m_root = new Ogre::Root(plugins_file, ogre_cfg_file, ogre_log);
		const Ogre::RenderSystemList& renderers = m_root->getAvailableRenderers();
		Ogre::RenderSystem *renderSystem = *(renderers.begin());
		m_root->setRenderSystem(renderSystem);
		QString dimensions = QString( "%1x%2" )
						.arg(width)
						.arg(height);

		renderSystem->setConfigOption( "Video Mode", dimensions.toStdString() );
		m_root->getRenderSystem()->setConfigOption( "Full Screen", "No" );
		m_root->saveConfig();
		m_root->initialise(false);
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::initOgre " << e.what();
	}
}

bool OgreRenderContext::locateResources(const char* cfgfile)
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
		LERR_ << "OgreRenderContext::locateResources exception" << e.what();
		return false;
	}
	return true;
}

bool OgreRenderContext::loadAllResources()
{
	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch(Ogre::Exception e)
	{
		LERR_ << "OgreRenderContext::loadAllResources exception" << e.what();
		return false;
	}
	return true;
}
