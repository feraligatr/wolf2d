#include "pch/pch.h"

#include "WolfGame.h"
#include "math/trMath.h"

#include "trFStream.h"

#include "WolfTerrain.h"

#define GRID_SIZE 1
#define GRID_COLS 64
#define GRID_ROWS 64

WolfGame::WolfGame(GraphicsWorld& gw, tree::PhysicsWorld& pw)
	:Game(gw, pw),
	m_objRoot(NULL),
	m_camera(NULL),
	m_terrain(NULL),
	m_player(NULL)
{
}

WolfGame::~WolfGame()
{
	delete m_objRoot;
	delete m_terrain;
}

void WolfGame::onMouseEvent(tree::MouseEvent& evt)
{
	
}

void WolfGame::onKeyEvent(tree::KeyEvent& evt)
{
}

void WolfGame::onHandleMessage(Message* message)
{
}

void WolfGame::update(float dt)
{
	m_objRoot->update(dt);
}

bool WolfGame::init()
{
	// TODO: init level and setup Scene.
	// split two steps.
	// 1. init level into WolfLevel.
	// 2. create scene by WolfLevel.

	// current there is not any level exist. so fake start. 
	// but including terrain, skybox, 

	fakeResources();

	try
	{
		r_gw.setSkyBox("Examples/SpaceSkyBox", 5000);

		// set light.
		r_gw.setAmbientLight(1, 1, 1);

		m_camera = r_gw.createCamera("wolf");
		m_camera->setPosition(tree::Vec3(0, 0, -10));
		m_camera->lookAt(tree::Vec3(0, 0, 0));
		m_camera->setClipDistance(1, 5001);
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "WolfGame::init exception" << e.what();
		return false;
	}

	if (!initLevel("../../Media/wolf/maps/s00.map"))
	{
		return false;
	}

	return true;
}

bool WolfGame::initLevel(const std::string& path)
{
	tree::FStream s(path);
	WolfLevel* levelData = WolfLevel::createLevelFromStream(s);

	if (!levelData)
	{
		return false;
	}

	// TODO: construct the whole game, move to a new function.

	// create root obj
	m_objRoot = new GameObject();

	// create terrain.
	m_terrain = new WolfTerrain(&r_gw, &r_pw, levelData);

	m_objRoot->addChild(m_terrain);

	// the walls is to render all walls, including transparent and pushing walls.
	// use manual object to generate the walls on the fly.
	//	m_walls = new WolfWalls(m_terrain);

	// Doors?
	// m_doors

	// floating objects like memo, gun, health.

	// temporary effect like gun fire and bullet run.


	// 
	//	m_player = new WolfPlayer(m_terrain);
	// construct enemys;
	

	delete levelData;

	return true;
}

#ifdef _FAKE_

// include OgreGraphicsWorld and get Ogre things to create ......

void WolfGame::fakeResources()
{
	// create some resource will be add into resources, but 
	// currently fake init by manual.

	// TODO: create plane as initial terrain appr.

	try
	{
		Ogre::Plane oceanSurface;
		oceanSurface.normal = Ogre::Vector3::UNIT_Y;
		oceanSurface.d = 0;
		Ogre::MeshManager::getSingleton().createPlane("TerrainMesh",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			oceanSurface,
			GRID_COLS, GRID_ROWS, GRID_COLS, GRID_ROWS, true, 1, 8, 8, Ogre::Vector3::UNIT_Y);
	}
	catch (Ogre::Exception e)
	{
		LERR_ << "WolfGame::fakeResources exception" << e.what();
	}
}

#endif /* _FAKE_ */
