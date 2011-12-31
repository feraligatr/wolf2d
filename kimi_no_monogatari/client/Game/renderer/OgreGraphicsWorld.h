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
	virtual ~OgreGraphicsWorld();

	virtual GWEntity* getRoot();

	virtual void setSkyBox(const std::string& skybox_rs, float distance);
	virtual void setAmbientLight(float r, float g, float b);

	virtual GWEntity* createEntity(const std::string& meshName, const std::string& matName);

	Ogre::SceneManager* getOgreSceneManager() {
		return m_sceneManager;
	}

private:
	void _createOgreSceneManager();

private:
	GWEntity* m_rootEntity;

	typedef std::set<GWEntity*> EntityList;
	EntityList m_allEntitys;

	// Ogre.
	// SceneManager is GraphicsWorld. other variable is helper for this.
	Ogre::SceneManager* m_sceneManager;
	Ogre::Root* m_ogreRoot;
	Ogre::RenderWindow* m_renderWindow;
	Ogre::Viewport* m_viewport;
};

#endif /* _OGRE_GRAPHICS_WORLD_H_ */
