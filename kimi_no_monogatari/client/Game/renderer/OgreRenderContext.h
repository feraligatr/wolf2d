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
	OgreRenderContext::OgreRenderContext();
	virtual ~OgreRenderContext();
	virtual GraphicsWorld* createGraphicsWorld();
	virtual void destroyGraphicsWorld(GraphicsWorld* world);
	virtual bool locateResources(const char* cfgfile);
	virtual bool loadAllResources();
	virtual void resize(int width, int height);
	
	virtual void exit();
	virtual void render();

	bool start(int windowId, int width, int height);

	WId getWindowId() const;

private:
	void initOgre(const std::string& plugins_file,
		const std::string& ogre_cfg_file,
		const std::string& ogre_log,
		int width, int height);

	void createRenderWindow(int windowId, int width, int height);

private:
	typedef std::set<GraphicsWorld*> GraphicsWorldList;
	GraphicsWorldList m_worlds;

	// Ogre things. 
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_renderWindow;

	int m_width, m_height;
};

#endif /* OGRE_RENDER_CONTEXT_H_ */
