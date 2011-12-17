#include "pch/pch.h"

#include "Sample3DGame.h"
#include <QString>
#include "Ogre.h"


Sample3DGame::Sample3DGame(GameContext* context, GameListener* listener)
:Game(context, listener)
,m_sceneManager(NULL)
,m_camera(NULL)
,m_root(NULL)
,m_renderWindow(NULL)
,m_viewport(NULL)
{

}

bool Sample3DGame::start(int width, int height)
{
	initOgre("plugins_d.cfg", "resources_d.cfg", "output.log", width, height);
	createRenderWindow(m_gameContext->getWindowId(), width, height);
	setupScene();
	return true;
}

void Sample3DGame::exit()
{
	if (m_root)
	{
		m_root->shutdown();
		delete m_root;
	}
}

void Sample3DGame::resize(int width, int height)
{
	m_renderWindow->windowMovedOrResized();
}

void Sample3DGame::intenal_update(float )
{
	// do nothing.
	m_root->renderOneFrame();
}

void Sample3DGame::createRenderWindow(int windowId, int width, int height)
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

void Sample3DGame::initOgre(const std::string& plugins_file,
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

void Sample3DGame::setupScene()
{
	Ogre::SceneType scene_manager_type = Ogre::ST_EXTERIOR_CLOSE;

	m_sceneManager = m_root->createSceneManager( scene_manager_type );
	m_sceneManager->setAmbientLight( Ogre::ColourValue(1,1,1) );

	m_camera = m_sceneManager->createCamera( "sample_cam" );
	m_camera->setPosition( Ogre::Vector3(0,1,0) );
	m_camera->lookAt( Ogre::Vector3(0,0,0) );
	m_camera->setNearClipDistance( 1.0 );

	m_viewport = m_renderWindow->addViewport( m_camera );
	m_viewport->setBackgroundColour( Ogre::ColourValue( 0,0,0 ) );
}
