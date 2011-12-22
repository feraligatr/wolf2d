#ifndef _GRAPHICS_WORLD_H_
#define _GRAPHICS_WORLD_H_

class GraphicsWorld
{
public:
	virtual ~GraphicsWorld() {}

	virtual bool start() = 0;

	virtual bool locateResources(const char* cfgfile) = 0;
	virtual bool loadAllResources() = 0;
	
};

#endif /* _GRAPHICS_WORLD_H_ */
