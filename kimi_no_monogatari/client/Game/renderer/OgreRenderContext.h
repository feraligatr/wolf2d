#ifndef OGRE_RENDER_CONTEXT_H_
#define OGRE_RENDER_CONTEXT_H_

#include "RenderContext.h"

class OgreGraphicsWorld;

namespace Ogre
{
	class RenderWindow;
	class Root;
}

class OgreRenderContext : public RenderContext
{
public:
	OgreRenderContext::OgreRenderContext(int windowId);
	virtual ~OgreRenderContext();
	virtual GraphicsWorld* getGraphicsWorld();
	virtual void resize(int width, int height);
	virtual bool start(int width, int height);
	virtual void exit();
	virtual void render();
private:
	void initOgre(const std::string& plugins_file,
		const std::string& ogre_cfg_file,
		const std::string& ogre_log,
		int width, int height);

	void createRenderWindow(int windowId, int width, int height);

private:
	OgreGraphicsWorld* m_gWorld;
	int m_windowId;

	// Ogre things. 
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_renderWindow;
};

#endif /* OGRE_RENDER_CONTEXT_H_ */
