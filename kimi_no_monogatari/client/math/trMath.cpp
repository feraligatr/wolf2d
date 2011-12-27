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

#include "pch/pch.h"

#include "trMath.h"

namespace tree
{

	const Real Math::POS_INFINITY = std::numeric_limits<Real>::infinity();
	const Real Math::NEG_INFINITY = -std::numeric_limits<Real>::infinity();
	const Real Math::PI = Real( 4.0 * atan( 1.0 ) );
	const Real Math::TWO_PI = Real( 2.0 * PI );
	const Real Math::HALF_PI = Real( 0.5 * PI );
	const Real Math::fDeg2Rad = PI / Real(180.0);
	const Real Math::fRad2Deg = Real(180.0) / PI;
	const Real Math::LOG2 = log(Real(2.0));

	const Vec3 Vec3::ZERO( 0, 0, 0 );

	const Vec3 Vec3::UNIT_X( 1, 0, 0 );
	const Vec3 Vec3::UNIT_Y( 0, 1, 0 );
	const Vec3 Vec3::UNIT_Z( 0, 0, 1 );
	const Vec3 Vec3::NEGATIVE_UNIT_X( -1,  0,  0 );
	const Vec3 Vec3::NEGATIVE_UNIT_Y(  0, -1,  0 );
	const Vec3 Vec3::NEGATIVE_UNIT_Z(  0,  0, -1 );
	const Vec3 Vec3::UNIT_SCALE(1, 1, 1);

	const Vec4 Vec4::ZERO( 0, 0, 0, 0 );

	const Quat Quat::ZERO(0.0,0.0,0.0,0.0);
	const Quat Quat::IDENTITY(1.0,0.0,0.0,0.0);

	//-----------------------------------------------------------------------
	void Quat::FromRotationMatrix (const Mat3& kRot)
	{
		// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
		// article "Quat Calculus and Fast Animation".

		Real fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
		Real fRoot;

		if ( fTrace > 0.0 )
		{
			// |w| > 1/2, may as well choose w > 1/2
			fRoot = Math::sqrt(fTrace + 1.0f);  // 2w
			w = 0.5f*fRoot;
			fRoot = 0.5f/fRoot;  // 1/(4w)
			x = (kRot[2][1]-kRot[1][2])*fRoot;
			y = (kRot[0][2]-kRot[2][0])*fRoot;
			z = (kRot[1][0]-kRot[0][1])*fRoot;
		}
		else
		{
			// |w| <= 1/2
			static size_t s_iNext[3] = { 1, 2, 0 };
			size_t i = 0;
			if ( kRot[1][1] > kRot[0][0] )
				i = 1;
			if ( kRot[2][2] > kRot[i][i] )
				i = 2;
			size_t j = s_iNext[i];
			size_t k = s_iNext[j];

			fRoot = Math::sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
			Real* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = 0.5f*fRoot;
			fRoot = 0.5f/fRoot;
			w = (kRot[k][j]-kRot[j][k])*fRoot;
			*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
			*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
		}
	}

	void Quat::ToRotationMatrix (Mat3& kRot) const
	{
		Real fTx  = x+x;
		Real fTy  = y+y;
		Real fTz  = z+z;
		Real fTwx = fTx*w;
		Real fTwy = fTy*w;
		Real fTwz = fTz*w;
		Real fTxx = fTx*x;
		Real fTxy = fTy*x;
		Real fTxz = fTz*x;
		Real fTyy = fTy*y;
		Real fTyz = fTz*y;
		Real fTzz = fTz*z;

		kRot[0][0] = 1.0f-(fTyy+fTzz);
		kRot[0][1] = fTxy-fTwz;
		kRot[0][2] = fTxz+fTwy;
		kRot[1][0] = fTxy+fTwz;
		kRot[1][1] = 1.0f-(fTxx+fTzz);
		kRot[1][2] = fTyz-fTwx;
		kRot[2][0] = fTxz-fTwy;
		kRot[2][1] = fTyz+fTwx;
		kRot[2][2] = 1.0f-(fTxx+fTyy);
	}

	void Quat::FromAngleAxis (Real rfAngle,
		const Vec3& rkAxis)
	{
		// assert:  axis[] is unit length
		//
		// The Quat representing the rotation is
		//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

		Real fHalfAngle ( 0.5*rfAngle );
		Real fSin = Math::sin(fHalfAngle);
		w = Math::cos(fHalfAngle);
		x = fSin*rkAxis.x;
		y = fSin*rkAxis.y;
		z = fSin*rkAxis.z;
	}

	void Quat::ToAngleAxis (Real rfAngle, Vec3& rkAxis) const
	{
		// The Quat representing the rotation is
		//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

		Real fSqrLength = x*x+y*y+z*z;
		if ( fSqrLength > 0.0 )
		{
			rfAngle = 2.0*Math::acos(w);
			Real fInvLength = Math::invSqrt(fSqrLength);
			rkAxis.x = x*fInvLength;
			rkAxis.y = y*fInvLength;
			rkAxis.z = z*fInvLength;
		}
		else
		{
			// angle is 0 (mod 2*pi), so any axis will do
			rfAngle = (0.0);
			rkAxis.x = 1.0;
			rkAxis.y = 0.0;
			rkAxis.z = 0.0;
		}
	}

	void Quat::FromAxes (const Vec3& xaxis, const Vec3& yaxis, const Vec3& zaxis)
	{
		Mat3 kRot;

		kRot[0][0] = xaxis.x;
		kRot[1][0] = xaxis.y;
		kRot[2][0] = xaxis.z;

		kRot[0][1] = yaxis.x;
		kRot[1][1] = yaxis.y;
		kRot[2][1] = yaxis.z;

		kRot[0][2] = zaxis.x;
		kRot[1][2] = zaxis.y;
		kRot[2][2] = zaxis.z;

		FromRotationMatrix(kRot);

	}

	void Quat::ToAxes (Vec3& xaxis, Vec3& yaxis, Vec3& zaxis) const
	{
		Mat3 kRot;

		ToRotationMatrix(kRot);

		xaxis.x = kRot[0][0];
		xaxis.y = kRot[1][0];
		xaxis.z = kRot[2][0];

		yaxis.x = kRot[0][1];
		yaxis.y = kRot[1][1];
		yaxis.z = kRot[2][1];

		zaxis.x = kRot[0][2];
		zaxis.y = kRot[1][2];
		zaxis.z = kRot[2][2];
	}

	Quat Quat::Inverse () const
	{
		Real fNorm = w*w+x*x+y*y+z*z;
		if ( fNorm > 0.0 )
		{
			Real fInvNorm = 1.0f/fNorm;
			return Quat(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
		}
		else
		{
			// return an invalid result to flag the error
			return ZERO;
		}
	}

	Real Quat::Norm () const
	{
		return w*w+x*x+y*y+z*z;
	}

	Real Quat::normalise(void)
	{
		Real len = Norm();
		Real factor = 1.0f / Math::sqrt(len);
		*this = *this * factor;
		return len;
	}

	Quat Quat::operator+ (const Quat& rkQ) const
	{
		return Quat(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
	}
	//-----------------------------------------------------------------------
	Quat Quat::operator- (const Quat& rkQ) const
	{
		return Quat(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
	}
	//-----------------------------------------------------------------------
	Quat Quat::operator* (const Quat& rkQ) const
	{
		// NOTE:  Multiplication is not generally commutative, so in most
		// cases p*q != q*p.

		return Quat
			(
			w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
			w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
			w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
			w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
			);
	}
	//-----------------------------------------------------------------------
	Quat Quat::operator* (Real fScalar) const
	{
		return Quat(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
	}

	Quat Quat::operator- () const
	{
		return Quat(-w,-x,-y,-z);
	}

	Vec3 Quat::operator* (const Vec3& v) const
	{
		// nVidia SDK implementation
		Vec3 uv, uuv;
		Vec3 qvec(x, y, z);
		uv = qvec.cross(v);
		uuv = qvec.cross(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return v + uv + uuv;

	}

	// Mat3

	const Mat3 Mat3::ZERO(0,0,0,0,0,0,0,0,0);
	const Mat3 Mat3::IDENTITY(1,0,0,0,1,0,0,0,1);

	void Mat3::SetColumn(size_t iCol, const Vec3& vec)
	{
		assert( 0 <= iCol && iCol < 3 );
		m[0][iCol] = vec.x;
		m[1][iCol] = vec.y;
		m[2][iCol] = vec.z;

	}

	void Mat3::FromAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis)
	{
		SetColumn(0,xAxis);
		SetColumn(1,yAxis);
		SetColumn(2,zAxis);

	}

	bool Mat3::operator== (const Mat3& rkMatrix) const
	{
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				if ( m[iRow][iCol] != rkMatrix.m[iRow][iCol] )
					return false;
			}
		}

		return true;
	}
	//-----------------------------------------------------------------------
	Mat3 Mat3::operator+ (const Mat3& rkMatrix) const
	{
		Mat3 kSum;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kSum.m[iRow][iCol] = m[iRow][iCol] +
					rkMatrix.m[iRow][iCol];
			}
		}
		return kSum;
	}
	//-----------------------------------------------------------------------
	Mat3 Mat3::operator- (const Mat3& rkMatrix) const
	{
		Mat3 kDiff;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kDiff.m[iRow][iCol] = m[iRow][iCol] -
					rkMatrix.m[iRow][iCol];
			}
		}
		return kDiff;
	}
	//-----------------------------------------------------------------------
	Mat3 Mat3::operator* (const Mat3& rkMatrix) const
	{
		Mat3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kProd.m[iRow][iCol] =
					m[iRow][0]*rkMatrix.m[0][iCol] +
					m[iRow][1]*rkMatrix.m[1][iCol] +
					m[iRow][2]*rkMatrix.m[2][iCol];
			}
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Vec3 Mat3::operator* (const Vec3& rkPoint) const
	{
		Vec3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				m[iRow][0]*rkPoint[0] +
				m[iRow][1]*rkPoint[1] +
				m[iRow][2]*rkPoint[2];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Vec3 operator* (const Vec3& rkPoint, const Mat3& rkMatrix)
	{
		Vec3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				rkPoint[0]*rkMatrix.m[0][iRow] +
				rkPoint[1]*rkMatrix.m[1][iRow] +
				rkPoint[2]*rkMatrix.m[2][iRow];
		}
		return kProd;
	}

	Mat3 Mat3::operator- () const
	{
		Mat3 kNeg;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kNeg[iRow][iCol] = -m[iRow][iCol];
		}
		return kNeg;
	}
	//-----------------------------------------------------------------------
	Mat3 Mat3::operator* (Real fScalar) const
	{
		Mat3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kProd[iRow][iCol] = fScalar*m[iRow][iCol];
		}
		return kProd;
	}

	Mat3 Mat3::Transpose () const
	{
		Mat3 kTranspose;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kTranspose[iRow][iCol] = m[iCol][iRow];
		}
		return kTranspose;
	}
	//-----------------------------------------------------------------------
	bool Mat3::Inverse (Mat3& rkInverse, Real fTolerance) const
	{
		// Invert a 3x3 using cofactors.  This is about 8 times faster than
		// the Numerical Recipes code which uses Gaussian elimination.

		rkInverse[0][0] = m[1][1]*m[2][2] -
			m[1][2]*m[2][1];
		rkInverse[0][1] = m[0][2]*m[2][1] -
			m[0][1]*m[2][2];
		rkInverse[0][2] = m[0][1]*m[1][2] -
			m[0][2]*m[1][1];
		rkInverse[1][0] = m[1][2]*m[2][0] -
			m[1][0]*m[2][2];
		rkInverse[1][1] = m[0][0]*m[2][2] -
			m[0][2]*m[2][0];
		rkInverse[1][2] = m[0][2]*m[1][0] -
			m[0][0]*m[1][2];
		rkInverse[2][0] = m[1][0]*m[2][1] -
			m[1][1]*m[2][0];
		rkInverse[2][1] = m[0][1]*m[2][0] -
			m[0][0]*m[2][1];
		rkInverse[2][2] = m[0][0]*m[1][1] -
			m[0][1]*m[1][0];

		Real fDet =
			m[0][0]*rkInverse[0][0] +
			m[0][1]*rkInverse[1][0]+
			m[0][2]*rkInverse[2][0];

		if ( Math::abs(fDet) <= fTolerance )
			return false;

		Real fInvDet = 1.0f/fDet;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				rkInverse[iRow][iCol] *= fInvDet;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	Mat3 Mat3::Inverse (Real fTolerance) const
	{
		Mat3 kInverse = Mat3::ZERO;
		Inverse(kInverse,fTolerance);
		return kInverse;
	}

	Real Mat3::Determinant () const
	{
		Real fCofactor00 = m[1][1]*m[2][2] -
			m[1][2]*m[2][1];
		Real fCofactor10 = m[1][2]*m[2][0] -
			m[1][0]*m[2][2];
		Real fCofactor20 = m[1][0]*m[2][1] -
			m[1][1]*m[2][0];

		Real fDet =
			m[0][0]*fCofactor00 +
			m[0][1]*fCofactor10 +
			m[0][2]*fCofactor20;

		return fDet;
	}

	// mat4

	const Mat4 Mat4::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0 );

	const Mat4 Mat4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 );

	inline static Real
		MINOR(const Mat4& m, const size_t r0, const size_t r1, const size_t r2, 
		const size_t c0, const size_t c1, const size_t c2)
	{
		return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
			m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
			m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
	}

	Real Mat4::determinant() const
	{
		return m[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
			m[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
			m[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
			m[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
	}

	Mat4 Mat4::inverse() const
	{
		Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
		Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
		Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
		Real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

		Real v0 = m20 * m31 - m21 * m30;
		Real v1 = m20 * m32 - m22 * m30;
		Real v2 = m20 * m33 - m23 * m30;
		Real v3 = m21 * m32 - m22 * m31;
		Real v4 = m21 * m33 - m23 * m31;
		Real v5 = m22 * m33 - m23 * m32;

		Real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
		Real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
		Real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
		Real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

		Real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

		Real d00 = t00 * invDet;
		Real d10 = t10 * invDet;
		Real d20 = t20 * invDet;
		Real d30 = t30 * invDet;

		Real d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Real d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Real d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Real d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		Real d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Real d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Real d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Real d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		Real d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Real d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Real d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Real d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		return Mat4(
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33);
	}
	//-----------------------------------------------------------------------
	Mat4 Mat4::inverseAffine(void) const
	{
		assert(isAffine());

		Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2];
		Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

		Real t00 = m22 * m11 - m21 * m12;
		Real t10 = m20 * m12 - m22 * m10;
		Real t20 = m21 * m10 - m20 * m11;

		Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2];

		Real invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

		t00 *= invDet; t10 *= invDet; t20 *= invDet;

		m00 *= invDet; m01 *= invDet; m02 *= invDet;

		Real r00 = t00;
		Real r01 = m02 * m21 - m01 * m22;
		Real r02 = m01 * m12 - m02 * m11;

		Real r10 = t10;
		Real r11 = m00 * m22 - m02 * m20;
		Real r12 = m02 * m10 - m00 * m12;

		Real r20 = t20;
		Real r21 = m01 * m20 - m00 * m21;
		Real r22 = m00 * m11 - m01 * m10;

		Real m03 = m[0][3], m13 = m[1][3], m23 = m[2][3];

		Real r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
		Real r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
		Real r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

		return Mat4(
			r00, r01, r02, r03,
			r10, r11, r12, r13,
			r20, r21, r22, r23,
			0,   0,   0,   1);
	}
	//-----------------------------------------------------------------------
	void Mat4::makeTransform(const Vec3& position, const Vec3& scale, const Quat& orientation)
	{
		// Ordering:
		//    1. Scale
		//    2. Rotate
		//    3. Translate

		Mat3 rot3x3;
		orientation.ToRotationMatrix(rot3x3);

		// Set up final matrix with scale, rotation and translation
		m[0][0] = scale.x * rot3x3[0][0]; m[0][1] = scale.y * rot3x3[0][1]; m[0][2] = scale.z * rot3x3[0][2]; m[0][3] = position.x;
		m[1][0] = scale.x * rot3x3[1][0]; m[1][1] = scale.y * rot3x3[1][1]; m[1][2] = scale.z * rot3x3[1][2]; m[1][3] = position.y;
		m[2][0] = scale.x * rot3x3[2][0]; m[2][1] = scale.y * rot3x3[2][1]; m[2][2] = scale.z * rot3x3[2][2]; m[2][3] = position.z;

		// No projection term
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	}
	//-----------------------------------------------------------------------
	void Mat4::makeInverseTransform(const Vec3& position, const Vec3& scale, const Quat& orientation)
	{
		// Invert the parameters
		Vec3 invTranslate = -position;
		Vec3 invScale(1 / scale.x, 1 / scale.y, 1 / scale.z);
		Quat invRot = orientation.Inverse();

		// Because we're inverting, order is translation, rotation, scale
		// So make translation relative to scale & rotation
		invTranslate = invRot * invTranslate; // rotate
		invTranslate *= invScale; // scale

		// Next, make a 3x3 rotation matrix
		Mat3 rot3x3;
		invRot.ToRotationMatrix(rot3x3);

		// Set up final matrix with scale, rotation and translation
		m[0][0] = invScale.x * rot3x3[0][0]; m[0][1] = invScale.x * rot3x3[0][1]; m[0][2] = invScale.x * rot3x3[0][2]; m[0][3] = invTranslate.x;
		m[1][0] = invScale.y * rot3x3[1][0]; m[1][1] = invScale.y * rot3x3[1][1]; m[1][2] = invScale.y * rot3x3[1][2]; m[1][3] = invTranslate.y;
		m[2][0] = invScale.z * rot3x3[2][0]; m[2][1] = invScale.z * rot3x3[2][1]; m[2][2] = invScale.z * rot3x3[2][2]; m[2][3] = invTranslate.z;		

		// No projection term
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	}

	const AABB AABB::BOX_NULL;
	const AABB AABB::BOX_INFINITE(AABB::EXTENT_INFINITE);

	Plane::Plane ()
	{
		normal = Vec3::ZERO;
		d = 0.0;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Plane& rhs)
	{
		normal = rhs.normal;
		d = rhs.d;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vec3& rkNormal, Real fConstant)
	{
		normal = rkNormal;
		d = -fConstant;
	}
	//---------------------------------------------------------------------
	Plane::Plane (Real a, Real b, Real c, Real _d)
		: normal(a, b, c), d(_d)
	{
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vec3& rkNormal, const Vec3& rkPoint)
	{
		redefine(rkNormal, rkPoint);
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vec3& rkPoint0, const Vec3& rkPoint1,
		const Vec3& rkPoint2)
	{
		redefine(rkPoint0, rkPoint1, rkPoint2);
	}
	//-----------------------------------------------------------------------
	Real Plane::getDistance (const Vec3& rkPoint) const
	{
		return normal.dot(rkPoint) + d;
	}

	//-----------------------------------------------------------------------
	void Plane::redefine(const Vec3& rkPoint0, const Vec3& rkPoint1,
		const Vec3& rkPoint2)
	{
		Vec3 kEdge1 = rkPoint1 - rkPoint0;
		Vec3 kEdge2 = rkPoint2 - rkPoint0;
		normal = kEdge1.cross(kEdge2);
		normal.normalise();
		d = -normal.dot(rkPoint0);
	}
	//-----------------------------------------------------------------------
	void Plane::redefine(const Vec3& rkNormal, const Vec3& rkPoint)
	{
		normal = rkNormal;
		d = -rkNormal.dot(rkPoint);
	}
	//-----------------------------------------------------------------------
	Vec3 Plane::projectVector(const Vec3& p) const
	{
		// We know plane normal is unit length, so use simple method
		Mat3 xform;
		xform[0][0] = 1.0f - normal.x * normal.x;
		xform[0][1] = -normal.x * normal.y;
		xform[0][2] = -normal.x * normal.z;
		xform[1][0] = -normal.y * normal.x;
		xform[1][1] = 1.0f - normal.y * normal.y;
		xform[1][2] = -normal.y * normal.z;
		xform[2][0] = -normal.z * normal.x;
		xform[2][1] = -normal.z * normal.y;
		xform[2][2] = 1.0f - normal.z * normal.z;
		return xform * p;

	}
	//-----------------------------------------------------------------------
	Real Plane::normalise(void)
	{
		Real fLength = normal.length();

		// Will also work for zero-sized vectors, but will change nothing
		if (fLength > 1e-08f)
		{
			Real fInvLength = 1.0f / fLength;
			normal *= fInvLength;
			d *= fInvLength;
		}

		return fLength;
	}

}
