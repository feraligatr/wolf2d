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

class OgreGWEntity;
class OgreGWCamera;

class OgreGraphicsWorld : public GraphicsWorld
{
public:
	OgreGraphicsWorld(Ogre::Root* root, Ogre::RenderWindow* renderWindow, int width, int height);
	virtual ~OgreGraphicsWorld();

	virtual GWEntity* getRoot();

	virtual void setSkyBox(const std::string& skybox_rs, float distance);
	virtual void setAmbientLight(float r, float g, float b);

	virtual GWEntity* createEntity(const std::string& meshName, const std::string& matName);
	virtual void destroyEntity(GWEntity* entity);

	virtual GWCamera* createCamera(const std::string& name);
	virtual void setActiveCamera(GWCamera* camera);

	Ogre::SceneManager* getOgreSceneManager() {
		return m_sceneManager;
	}

	void resize(int width, int height);

private:
	void _createOgreSceneManager();

private:
	OgreGWEntity* m_rootEntity;

	typedef std::set<OgreGWEntity*> EntityList;
	EntityList m_allEntitys;

	typedef std::set<OgreGWCamera*> CameraList;
	CameraList m_allCameras;
	OgreGWCamera* m_activeCamera;

	// Ogre.
	// SceneManager is GraphicsWorld. other variable is helper for this.
	Ogre::SceneManager* m_sceneManager;
	Ogre::Root* m_ogreRoot;
	Ogre::RenderWindow* m_renderWindow;
	Ogre::Viewport* m_viewport;

	int m_width;
	int m_height;
};

#endif /* _OGRE_GRAPHICS_WORLD_H_ */
