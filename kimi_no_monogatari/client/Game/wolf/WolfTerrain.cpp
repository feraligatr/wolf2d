#include "pch/pch.h"

#include "WolfTerrain.h"

WolfTerrain::WolfTerrain(GraphicsWorld* gw, tree::PhysicsWorld* pw, WolfLevel* level)
:WolfGameObject(gw, pw)
{
	init(level);
}

WolfTerrain::~WolfTerrain()
{
}

void WolfTerrain::init(WolfLevel* level)
{
	createGraphicsEntity("TerrainMesh", "Examples/Rockwall");
	m_graphicsWorld->getRoot()->addChild(m_gwEntity);
	// the mesh is created by manual, and the size should be 64x64.
	// currently the size is 1, it should get from config.
}




