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

#ifndef _TR_MAT3_H_
#define _TR_MAT3_H_

#include "trVec.h"

namespace tree
{
	class Mat3
	{
	public:
		inline Mat3 () {}
		inline explicit Mat3 (const Real arr[3][3])
		{
			memcpy(m,arr,9*sizeof(Real));
		}
		inline Mat3 (const Mat3& rkMatrix)
		{
			memcpy(m,rkMatrix.m,9*sizeof(Real));
		}
		Mat3 (Real fEntry00, Real fEntry01, Real fEntry02,
			Real fEntry10, Real fEntry11, Real fEntry12,
			Real fEntry20, Real fEntry21, Real fEntry22)
		{
			m[0][0] = fEntry00;
			m[0][1] = fEntry01;
			m[0][2] = fEntry02;
			m[1][0] = fEntry10;
			m[1][1] = fEntry11;
			m[1][2] = fEntry12;
			m[2][0] = fEntry20;
			m[2][1] = fEntry21;
			m[2][2] = fEntry22;
		}

		/** Exchange the contents of this matrix with another. 
		*/
		inline void swap(Mat3& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
		}

		inline Real* operator[] (size_t iRow) const
		{
			return (Real*)m[iRow];
		}

		Vec3 GetColumn (size_t iCol) const;
		void SetColumn(size_t iCol, const Vec3& vec);
		void FromAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis);

		// assignment and comparison
		inline Mat3& operator= (const Mat3& rkMatrix)
		{
			memcpy(m,rkMatrix.m,9*sizeof(Real));
			return *this;
		}
		bool operator== (const Mat3& rkMatrix) const;
		inline bool operator!= (const Mat3& rkMatrix) const
		{
			return !operator==(rkMatrix);
		}

		// arithmetic operations
		Mat3 operator+ (const Mat3& rkMatrix) const;
		Mat3 operator- (const Mat3& rkMatrix) const;
		Mat3 operator* (const Mat3& rkMatrix) const;
		Mat3 operator- () const;

		// matrix * vector [3x3 * 3x1 = 3x1]
		Vec3 operator* (const Vec3& rkVector) const;

		// vector * matrix [1x3 * 3x3 = 1x3]
		friend Vec3 operator* (const Vec3& rkVector,
			const Mat3& rkMatrix);

		// matrix * scalar
		Mat3 operator* (Real fScalar) const;

		// utilities
		Mat3 Transpose () const;
		bool Inverse (Mat3& rkInverse, Real fTolerance = 1e-06) const;
		Mat3 Inverse (Real fTolerance = 1e-06) const;
		Real Determinant () const;

		static const Mat3 ZERO;
		static const Mat3 IDENTITY;

	protected:

		Real m[3][3];

		// for faster access
		friend class Mat4;
	};

}
#endif /* _TR_MAT3_H_ */
