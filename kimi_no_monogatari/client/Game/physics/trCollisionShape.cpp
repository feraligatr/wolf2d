#include "pch/pch.h"
#include "trCollisionShape.h"

namespace tree
{

CollisionShape::~CollisionShape()
{
	if (m_bulletShape && m_bulletShape->getShapeType() == COMPOUND_SHAPE_PROXYTYPE)
	{
		btCompoundShape* shape = (btCompoundShape*)m_bulletShape;
		for (int i = 0; i < shape->getNumChildShapes(); ++i)
		{
			delete shape->getChildShape(i);
		}
	}
	else if (m_bulletShape && m_bulletShape->getShapeType() == SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE)
	{
		btScaledBvhTriangleMeshShape* shape = (btScaledBvhTriangleMeshShape*)m_bulletShape;
		delete shape->getChildShape();
	}
	delete m_bulletShape;
	m_bulletShape = 0;
}

void CollisionShape::initBulletShape()
{
	CollisionShape* shape = this;
	if (m_bulletShape) return;
	{
		switch(shape->type)
		{
		case CollisionShape::SHAPE_SPHERE:
		case CollisionShape::SHAPE_CYLINDER:
		case CollisionShape::SHAPE_CYLINDER_X:
		case CollisionShape::SHAPE_CONE:
		case CollisionShape::SHAPE_BOX:
			m_bulletShape = _getSimpleBTShape(shape);
			break;
		case CollisionShape::SHAPE_PLANE:
			m_bulletShape = new btStaticPlaneShape(btVector3(0, 0, 1), shape->shapeDimensions.z());

			break;
		case CollisionShape::SHAPE_COMPOUND:
			m_bulletShape = new btCompoundShape();
			{
				CompoundShape* com_shape = (CompoundShape*)shape;
				for (size_t i = 0; i < com_shape->info.size(); ++i)
				{
					btTransform tr;
					tr = com_shape->info.at(i).second;
					btCollisionShape* sub_shape = _getSimpleBTShape(com_shape->info.at(i).first);
					((btCompoundShape*)m_bulletShape)->addChildShape(tr, sub_shape);
				}
			}
			break;
		case CollisionShape::SHAPE_STATICTRIANGLEMESH:
			{
				btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();
				StaticTriangleMeshShape* tri_shape = (StaticTriangleMeshShape*)shape;
				
				for (size_t i = 0; i < tri_shape->parts.size(); ++i)
				{
					const MeshPart& in_part = tri_shape->parts[i];
					btIndexedMesh part;
					part.m_vertexBase = (const unsigned char*)in_part.vertexBase;
					part.m_vertexStride = in_part.vertexStride;
					part.m_numVertices = in_part.numVertices;

					part.m_triangleIndexBase = (const unsigned char*)in_part.triangleIndexBase;
					part.m_triangleIndexStride = in_part.triangleIndexStride;
					part.m_numTriangles = in_part.triangleCounts;
					part.m_indexType = PHY_SHORT;
					
					meshInterface->addIndexedMesh(part,PHY_SHORT);
				}
				m_bulletShape = new btBvhTriangleMeshShape(meshInterface, true);
				if (shape->margin != 0)
					m_bulletShape->setMargin(shape->margin);
			}
			break;
		case CollisionShape::SHAPE_CONVEX_HULL:
			{
				ConvexHullShape* hull_shape = (ConvexHullShape*)shape;
				btConvexHullShape* temp_shape = new btConvexHullShape();
				for (size_t i = 0; i < hull_shape->vertices.size(); i += 3)
				{
					temp_shape->addPoint(btVector3(hull_shape->vertices[i], hull_shape->vertices[i + 1],
						hull_shape->vertices[i + 2]) * hull_shape->scale);
				}
				m_bulletShape = temp_shape;
			}
			break;
		default:
			ASSERT(false);
			break;
		}
	}
}

btCollisionShape* CollisionShape::_getSimpleBTShape(CollisionShape* shape)
{
	btCollisionShape* res = 0;
	switch(shape->type)
	{
	case CollisionShape::SHAPE_SPHERE:
		res = new btSphereShape(shape->shapeDimensions.x() * shape->scale);
		break;
	case CollisionShape::SHAPE_CYLINDER:
		res = new btCylinderShapeZ((shape->shapeDimensions) * shape->scale);
		break;
	case CollisionShape::SHAPE_CYLINDER_X:
		res = new btCylinderShapeX((shape->shapeDimensions) * shape->scale);
		break;
	case CollisionShape::SHAPE_CONE:
		res = new btConeShapeZ(shape->shapeDimensions.x() * shape->scale, shape->shapeDimensions.z() * 2.f * shape->scale);
		break;
	case CollisionShape::SHAPE_BOX:
		res = new btBoxShape((shape->shapeDimensions) * shape->scale);
		break;
	default:
		ASSERT(false);
		break;
	}
	return res;
}


}