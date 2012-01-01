#ifndef _GW_CAMERA_H_
#define _GW_CAMERA_H_

class GWCamera
{
public:
	virtual ~GWCamera() {}

	virtual void setPosition(const tree::Vec3& pos) = 0;
	virtual void setRotation(const tree::Quat& quat) = 0;

	virtual void lookAt(const tree::Vec3& pos) = 0;
	virtual void setClipDistance(float nearDist, float farDist) = 0;
};



#endif /* _GW_CAMERA_H_ */
