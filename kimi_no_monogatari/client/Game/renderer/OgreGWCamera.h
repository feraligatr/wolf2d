#ifndef _OGRE_GW_CAMERA_H_
#define _OGRE_GW_CAMERA_H_

#include "GWCamera.h"

class OgreGraphicsWorld;

class OgreGWCamera : public GWCamera
{
public:
	OgreGWCamera(OgreGraphicsWorld* gw, const std::string& name);
	virtual ~OgreGWCamera();

	virtual void setPosition(const tree::Vec3& pos);
	virtual void setRotation(const tree::Quat& quat);

	virtual void lookAt(const tree::Vec3& pos);
	virtual void setClipDistance(float nearDist, float farDist);

	Ogre::Camera* getOgreCamera() {
		return m_ogreCamera;
	}

private:
	OgreGraphicsWorld* m_gw;
	Ogre::Camera* m_ogreCamera;

};


#endif /* _OGRE_GW_CAMERA_H_ */
