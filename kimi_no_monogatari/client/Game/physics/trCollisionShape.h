#ifndef _TR_COLLISION_SHAPE_H_
#define _TR_COLLISION_SHAPE_H_

#include <vector>

class btCollisionShape;

namespace tree
{

class CollisionShape
{
public:
	enum SHAPE_TYPE
	{
		SHAPE_INVALID,

		SHAPE_CONE,
		SHAPE_SPHERE,
		SHAPE_CYLINDER,
		SHAPE_CYLINDER_X,
		SHAPE_BOX,
		SHAPE_COMPOUND,
		SHAPE_STATICTRIANGLEMESH,
		SHAPE_CONVEX_HULL,
		SHAPE_PLANE,
		SHAPE_NUM,
	};
public:
	CollisionShape()
		:type(SHAPE_INVALID),
		m_bulletShape(0),
		scale(1.0f),
		margin(0.0f)
	{

	}
	virtual ~CollisionShape();

	btCollisionShape* _getSimpleBTShape(CollisionShape* shape);

	void initBulletShape();

	btCollisionShape* m_bulletShape;

	int type;
	float margin;
	btVector3 shapeDimensions;
	float scale;	// temp add

};

class CompoundShape : public CollisionShape
{
public:
	CompoundShape()
	{
		type = SHAPE_COMPOUND;
	}
	typedef std::vector<std::pair<CollisionShape*, btTransform> > CompoundAdditionalInfo;

	CompoundAdditionalInfo info;
};

class MeshPart
{
public:
	int triangleCounts;
	unsigned char* triangleIndexBase;
	int triangleIndexStride;

	int numVertices;
	unsigned char* vertexBase;
	int vertexStride;
};

class StaticTriangleMeshShape : public CollisionShape
{
public:
	StaticTriangleMeshShape()
	{
		type = SHAPE_STATICTRIANGLEMESH;
	}
	std::vector<MeshPart> parts;
};

class ConvexHullShape : public CollisionShape
{
public:
	ConvexHullShape()
	{
		type = SHAPE_CONVEX_HULL;
	}
//	std::vector<MeshPart> parts;
	std::vector<float> vertices;
};

}

#endif