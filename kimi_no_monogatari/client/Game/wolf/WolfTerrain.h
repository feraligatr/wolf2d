#ifndef _WOLF_TERRAIN_H_
#define _WOLF_TERRAIN_H_

#include "WolfGameObject.h"

#include "Wolf.h"

class WolfTerrain : public WolfGameObject
{
public:
	WolfTerrain(GraphicsWorld* gw, tree::PhysicsWorld* pw, WolfLevel* level);
	virtual ~WolfTerrain();

private:
	void init(WolfLevel* level);

};

#endif /* _WOLF_TERRAIN_H_ */
