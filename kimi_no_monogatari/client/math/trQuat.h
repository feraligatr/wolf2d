#ifndef _TR_QUAT_H_
#define _TR_QUAT_H_

#include "trMat3.h"

namespace tree
{

	class Quat
	{
	public:
		inline Quat(Real _w = 1.0, Real _x = 0.0, Real _y = 0.0, Real _z = 0.0)
		{
			w = _w;
			x = _x;
			y = _y;
			z = _z;
		}

		inline Quat(const Mat3& rot)
		{
			this->FromRotationMatrix(rot);
		}
		inline Quat(Real rfAngle, const Vec3& rkAxis)
		{
			this->FromAngleAxis(rfAngle, rkAxis);
		}

		inline Quat(const Vec3& xaxis, const Vec3& yaxis, const Vec3& zaxis)
		{
			this->FromAxes(xaxis, yaxis, zaxis);
		}

		inline Quat(const Vec3* akAxis)
		{
			this->FromAxes(akAxis[0], akAxis[1], akAxis[2]);
		}
		/// Construct a Quat from 4 manual w/x/y/z values
		inline Quat(Real* valptr)
		{
			memcpy(&w, valptr, sizeof(Real)*4);
		}

		inline void swap(Quat& other)
		{
			std::swap(w, other.w);
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		inline Real operator [] ( const size_t i ) const
		{
			assert( i < 4 );

			return *(&w+i);
		}

		/// Array accessor operator
		inline Real& operator [] ( const size_t i )
		{
			assert( i < 4 );

			return *(&w+i);
		}

		/// Pointer accessor for direct copying
		inline Real* ptr()
		{
			return &w;
		}

		/// Pointer accessor for direct copying
		inline const Real* ptr() const
		{
			return &w;
		}

		Quat Inverse () const;  // apply to non-zero quaternion

		void FromRotationMatrix (const Mat3& kRot);
		void ToRotationMatrix (Mat3& kRot) const;
		void FromAngleAxis (Real rfAngle, const Vec3& rkAxis);
		void ToAngleAxis (Real rfAngle, Vec3& rkAxis) const;
		void FromAxes (const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis);
		void ToAxes (Vec3& xAxis, Vec3& yAxis, Vec3& zAxis) const;

		inline Quat& operator= (const Quat& rkQ)
		{
			w = rkQ.w;
			x = rkQ.x;
			y = rkQ.y;
			z = rkQ.z;
			return *this;
		}

		inline bool operator== (const Quat& rhs) const
		{
			return (rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
		}
		inline bool operator!= (const Quat& rhs) const
		{
			return !operator==(rhs);
		}

		Quat operator+ (const Quat& rkQ) const;
		Quat operator- (const Quat& rkQ) const;
		Quat operator* (const Quat& rkQ) const;
		Quat operator* (Real fScalar) const;
		Quat operator- () const;

		Real Norm () const;  // squared-length
		/// Normalises this Quat, and returns the previous length
		Real normalise(void); 

		// rotation of a vector by a Quat
		Vec3 operator* (const Vec3& rkVector) const;

		static Quat getRotationTo(const Vec3& src, const Vec3& dest,
			const Vec3& fallbackAxis = Vec3::ZERO)
		{
			// Based on Stan Melax's article in Game Programming Gems
			Quat q;
			// Copy, since cannot modify local
			Vec3 v0 = src;
			Vec3 v1 = dest;
			v0.normalise();
			v1.normalise();

			Real d = v0.dot(v1);
			// If dot == 1, vectors are the same
			if (d >= 1.0f)
			{
				return Quat::IDENTITY;
			}
			if (d < (1e-6f - 1.0f))
			{
				if (fallbackAxis != Vec3::ZERO)
				{
					// rotate 180 degrees about the fallback axis
					q.FromAngleAxis((Math::PI), fallbackAxis);
				}
				else
				{
					// Generate an axis
					Vec3 axis = Vec3::UNIT_X.cross(src);
					if (axis.isZeroLength()) // pick another if colinear
						axis = Vec3::UNIT_Y.cross(src);
					axis.normalise();
					q.FromAngleAxis((Math::PI), axis);
				}
			}
			else
			{
				Real s = sqrt( (1+d)*2 );
				Real invs = 1 / s;

				Vec3 c = v0.cross(v1);

				q.x = c.x * invs;
				q.y = c.y * invs;
				q.z = c.z * invs;
				q.w = s * 0.5f;
				q.normalise();
			}
			return q;
		}

		// special values
		static const Quat ZERO;
		static const Quat IDENTITY;

		Real w, x, y, z;
	};

}


#endif /* _TR_QUAT_ */
