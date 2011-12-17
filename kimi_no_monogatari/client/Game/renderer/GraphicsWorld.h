#ifndef _GRAPHICS_WORLD_H_
#define _GRAPHICS_WORLD_H_

class GraphicsWorld
{
public:
	virtual ~GraphicsWorld() {}

	virtual bool start() = 0;
	
};

#endif /* _GRAPHICS_WORLD_H_ */
