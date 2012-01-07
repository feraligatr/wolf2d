#ifndef _GW_ENTITY_H_
#define _GW_ENTITY_H_

class GraphicsWorld;

class GWEntity
{
public:
	virtual ~GWEntity() {}
	virtual void setPosition(const tree::Vec3& pos) = 0;
	virtual void setRotation(const tree::Quat& quat) = 0;
	virtual void setScale(const tree::Vec3& scale) = 0;

	// hierarchy.
	virtual void addChild(GWEntity* entity) = 0;
	virtual void removeChild(GWEntity* entity) = 0;
	virtual GWEntity* getParent() = 0;
	virtual u16 numChildren() = 0;

private:

};

#endif /* _GW_ENTITY_H_ */
