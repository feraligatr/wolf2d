#ifndef _OGRE_GRAPHICS_HELPER_H_
#define _OGRE_GRAPHICS_HELPER_H_

inline Ogre::Vector3 Vec3ToOgre(const tree::Vec3& pos)
{
	return Ogre::Vector3(pos.x(), pos.y(), pos.z());
}

inline Ogre::Quaternion QuatToOgre(const tree::Quat& quat)
{
	return Ogre::Quaternion(quat.w(), quat.x(), quat.y(), quat.z());
}

inline Ogre::Matrix3 Mat3ToOgre(const tree::Mat3& mat)
{
	return Ogre::Matrix3(mat[0][0], mat[0][1], mat[0][2],
						mat[1][0], mat[1][1], mat[1][2],
						mat[2][0], mat[2][1], mat[2][2]);
}

#endif /* _OGRE_GRAPHICS_HELPER_H_ */
