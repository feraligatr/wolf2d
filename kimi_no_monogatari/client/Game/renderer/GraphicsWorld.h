#ifndef _GRAPHICS_WORLD_H_
#define _GRAPHICS_WORLD_H_

// TODO. wrap Graphics into namespace graphics or some other names.


class GWEntity;
class GWCamera;

class GraphicsWorld
{
public:
	virtual ~GraphicsWorld() {}

	virtual GWEntity* createEntity(const std::string& meshName = "", const std::string& matName = "") = 0;
	virtual void destroyEntity(GWEntity* entity) = 0;
	virtual GWCamera* createCamera(const std::string& name) = 0;
	virtual void setActiveCamera(GWCamera* camera) = 0;

	virtual GWEntity* getRoot() = 0;

	virtual void setSkyBox(const std::string& skybox_rs, float far) = 0;
	virtual void setAmbientLight(float r, float g, float b) = 0;

};

#endif /* _GRAPHICS_WORLD_H_ */
