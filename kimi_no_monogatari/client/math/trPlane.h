/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
// This file is based on material originally from:
// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt


#ifndef __PlANE_H__
#define __PlANE_H__

#include "trVec.h"

namespace tree
{
	class Plane
	{
	public:
		/** Default constructor - sets everything to 0.
		*/
		Plane ();
		Plane (const Plane& rhs);
		/** Construct a plane through a normal, and a distance to move the plane along the normal.*/
		Plane (const Vec3& rkNormal, Real fConstant);
		/** Construct a plane using the 4 constants directly **/
		Plane (Real a, Real b, Real c, Real d);
		Plane (const Vec3& rkNormal, const Vec3& rkPoint);
		Plane (const Vec3& rkPoint0, const Vec3& rkPoint1,
			const Vec3& rkPoint2);

		/** This is a pseudodistance. The sign of the return value is
		positive if the point is on the positive side of the plane,
		negative if the point is on the negative side, and zero if the
		point is on the plane.
		@par
		The absolute value of the return value is the true distance only
		when the plane normal is a unit length vector.
		*/
		Real getDistance (const Vec3& rkPoint) const;

		/** Redefine this plane based on 3 points. */
		void redefine(const Vec3& rkPoint0, const Vec3& rkPoint1,
			const Vec3& rkPoint2);

		/** Redefine this plane based on a normal and a point. */
		void redefine(const Vec3& rkNormal, const Vec3& rkPoint);

		/** Project a vector onto the plane. 
		@remarks This gives you the element of the input vector that is perpendicular 
		to the normal of the plane. You can get the element which is parallel
		to the normal of the plane by subtracting the result of this method
		from the original vector, since parallel + perpendicular = original.
		@param v The input vector
		*/
		Vec3 projectVector(const Vec3& v) const;

		/** Normalises the plane.
		@remarks
		This method normalises the plane's normal and the length scale of d
		is as well.
		@note
		This function will not crash for zero-sized vectors, but there
		will be no changes made to their components.
		@returns The previous length of the plane's normal.
		*/
		Real normalise(void);

		Vec3 normal;
		Real d;

		/// Comparison operator
		bool operator==(const Plane& rhs) const
		{
			return (rhs.d == d && rhs.normal == normal);
		}
		bool operator!=(const Plane& rhs) const
		{
			return (rhs.d != d || rhs.normal != normal);
		}

	};

}

#endif /* __PlANE_H__ */
