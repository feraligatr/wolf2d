#ifndef _OGRE_GRAPHICS_WORLD_H_
#define _OGRE_GRAPHICS_WORLD_H_

#include "GraphicsWorld.h"

namespace Ogre
{
	class SceneManager;
	class RenderWindow;
	class Camera;
	class Viewport;
	class Root;
}

class OgreGraphicsWorld : public GraphicsWorld
{
public:
	OgreGraphicsWorld(Ogre::Root* root, Ogre::RenderWindow* renderWindow);
	virtual bool start();
	

	virtual bool locateResources(const char* cfgfile);
	virtual bool loadAllResources();

	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_renderWindow;
	Ogre::Viewport* m_viewport;
};

#endif /* _OGRE_GRAPHICS_WORLD_H_ */
