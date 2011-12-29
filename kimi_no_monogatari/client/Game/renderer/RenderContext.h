#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

// TODO: class AudioWorld;
class GraphicsWorld;

class RenderContext
{
public:
	virtual ~RenderContext() {}
	virtual GraphicsWorld* createGraphicsWorld(const char* name) = 0;
	virtual void destroyGraphicsWorld(GraphicsWorld* graphics) = 0;
	virtual bool locateResources(const char* cfgfile) = 0;
	virtual bool loadAllResources() = 0;
	virtual void resize(int width, int height) = 0;
	virtual bool start(int width, int height) = 0;
	virtual void exit() = 0;
	virtual void render() = 0;
};

#endif /* _RENDER_CONTEXT_H_ */
