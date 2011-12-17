#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

// TODO: class AudioWorld;
class GraphicsWorld;

class RenderContext
{
public:
	virtual ~RenderContext() {}
	virtual GraphicsWorld* getGraphicsWorld() = 0;
	virtual void resize(int width, int height) = 0;
	virtual bool start(int width, int height) = 0;
	virtual void exit() = 0;
};

#endif /* _RENDER_CONTEXT_H_ */
