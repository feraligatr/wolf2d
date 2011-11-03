#ifndef _SAMPLE_3D_GAME_H_
#define _SAMPLE_3D_GAME_H_

#include "Game.h"

#include <string>

namespace Ogre
{
	class SceneManager;
	class RenderWindow;
	class Camera;
	class Viewport;
	class Root;
	class Entity;
	class SceneNode;
	class Light;
}

class Sample3DGame : public Game
{
public:
	Sample3DGame(GameContext* context, GameListener* listener);
	virtual bool start(int width, int height);
	virtual void exit();

	virtual void resize(int width, int height);
protected:
	virtual void intenal_update(float dt);

	void initOgre(const std::string& plugins_file,
		const std::string& ogre_cfg_file,
		const std::string& ogre_log, int width, int height);
	void createRenderWindow(int windowId, int width, int height);
	void setupScene();

	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_renderWindow;
	Ogre::Viewport* m_viewport;

};


#endif /* _SAMPLE_3D_GAME_H_ */
