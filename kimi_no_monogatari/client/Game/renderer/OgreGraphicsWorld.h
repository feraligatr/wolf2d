#ifndef _OGRE_GRAPHICS_WORLD_H_
#define _OGRE_GRAPHICS_WORLD_H_

#include "GraphicsWorld.h"
#include "math/trMath.h"

namespace Ogre
{
	class SceneManager;
	class RenderWindow;
	class Camera;
	class Viewport;
	class Root;
}

class GWEntity;

class OgreGraphicsWorld : public GraphicsWorld
{
public:
	OgreGraphicsWorld(Ogre::Root* root, Ogre::RenderWindow* renderWindow);

	virtual GWEntity* getRoot();

	virtual void setSkyBox(const char* skybox_rs, float far);
	virtual void setAmbientLight(float r, float g, float b);

	Ogre::SceneManager* getOgreSceneManager() {
		return m_sceneManager;
	}

private:
	void _createOgreSceneManager();

private:
	GWEntity* m_rootNode;


	// Ogre.
	// SceneManager is GraphicsWorld. other variable is helper for this.
	Ogre::SceneManager* m_sceneManager;
	Ogre::Root* m_ogreRoot;
	Ogre::RenderWindow* m_renderWindow;
	Ogre::Viewport* m_viewport;
};

#endif /* _OGRE_GRAPHICS_WORLD_H_ */
