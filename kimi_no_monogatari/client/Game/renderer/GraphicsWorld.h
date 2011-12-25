#ifndef _GRAPHICS_WORLD_H_
#define _GRAPHICS_WORLD_H_

// TODO. wrap Graphics into namespace graphics or some other names.

class GWScene;

class GraphicsWorld
{
public:
	virtual ~GraphicsWorld() {}

	virtual bool start() = 0;

	virtual bool locateResources(const char* cfgfile) = 0;
	virtual bool loadAllResources() = 0;

	// TODO: add name and type as parameter?
	GWScene* createScene() = 0;


};

#endif /* _GRAPHICS_WORLD_H_ */
