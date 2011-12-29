#ifndef _GW_SCENE_H_
#define _GW_SCENE_H_

class GWEntity;
class GraphicsWorld;

class GWScene
{
public:
	GWScene(GraphicsWorld* world);

	virtual GWEntity* getRoot() = 0;

	virtual void setSkyBox(const char* skybox, float far) = 0;
	virtual void setAmbientLight(float r, float g, float b) = 0;

};


#endif /* _GW_SCENE_H_ */
