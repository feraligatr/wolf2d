#include "pch/pch.h"

#include "OgreRenderContext.h"
#include "OgreGraphicsWorld.h"
#include "Ogre.h"

#include <QString>

OgreRenderContext::OgreRenderContext(int windowId)
	:m_gWorld(NULL),
	 m_windowId(windowId)
{

}

OgreRenderContext::~OgreRenderContext()
{
	exit();
}

GraphicsWorld* OgreRenderContext::getGraphicsWorld()
{
	return m_gWorld;
}

void OgreRenderContext::resize(int , int )
{
	m_renderWindow->windowMovedOrResized();
}

bool OgreRenderContext::start(int width, int height)
{
	initOgre("plugins_d.cfg", "ogre_config.cfg", "output.log", width, height);
	createRenderWindow(m_windowId, width, height);
	ASSERT(m_gWorld == NULL);
	m_gWorld = new OgreGraphicsWorld(m_root, m_renderWindow);
	return m_gWorld->start();
}

void OgreRenderContext::exit()
{
	if (m_gWorld)
	{
		delete m_gWorld;
		m_gWorld = NULL;
	}
	if (m_root)
	{
		m_root->shutdown();
		delete m_root;
		m_root = NULL;
	}
}

void OgreRenderContext::render()
{
	m_root->renderOneFrame();
}

void OgreRenderContext::createRenderWindow(int windowId, int width, int height)
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
}

void OgreRenderContext::initOgre(const std::string& plugins_file,
		const std::string& ogre_cfg_file,
		const std::string& ogre_log,
		int width, int height)
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
