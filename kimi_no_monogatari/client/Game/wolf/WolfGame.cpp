#include "pch/pch.h"

#include "WolfGame.h"
#include "math/trMath.h"
#include "renderer/Graphics.h"

WolfGame::WolfGame(GraphicsWorld& gw)
	:Game(gw)
{
}

WolfGame::~WolfGame()
{
	r_gw.destroyScene(m_scene);
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

	m_scene = r_gw.createScene();

	m_scene->setSkyBox("Examples/SpaceSkyBox", 5000);

	// set light.
	m_scene->setAmbientLight(0.3, 0.3, 0.3);

	m_terrain = new WolfTerrain(NULL);
	// the terrain is root object in the scene. 
	// add Physics World(Grid Physics World).
	// Every Game Object can has a physics object. 

	m_terrain->init(m_scene);

	// the walls is to render all walls, including transparent and pushing walls. 
	// use manual object to generate the walls on the fly.
	m_walls = new WolfWalls(m_terrain);

	// Doors?
	// m_doors

	// floating objects like memo, gun, health.

	// temporary effect like gun fire and bullet run.


	// 
	m_player = new WolfPlayer(m_terrain);
	// construct enemys;
	

	return true;
}

#ifdef _FAKE_

// include OgreGraphicsWorld and get Ogre things to create ......

void WolfGame::fakeResources()
{
	// create some resource will be add into resources, but 
	// currently fake init by manual.

	// TODO: create plane as initial terrain appr.
}

#endif /* _FAKE_ */
