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

#ifndef _TR_VEC_H_
#define _TR_VEC_H_

namespace tree
{

	class Vec3
	{
	public:
		Real x, y, z;

	public:
		inline Vec3() {}
		inline Vec3(Real x_, Real y_, Real z_)
			:x(x_), y(y_), z(z_)
		{

		}

		inline explicit Vec3(Real coordinate[3])
			: x(coordinate[0]),
			y(coordinate[1]),
			z(coordinate[2])
		{

		}

		inline explicit Vec3(int coordinate[3])
		{
			x = (Real)coordinate[0];
			y = (Real)coordinate[1];
			z = (Real)coordinate[2];
		}

		inline explicit Vec3(const Real* r)
			:x( r[0] ), y( r[1] ), z( r[2] )
		{
		}

		inline explicit Vec3(Real scalar)
			: x(scalar)
			, y(scalar)
			, z(scalar)
		{
		}

		inline void swap(Vec3& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		inline Real operator [] (const size_t i) const
		{
			assert(i < 3);

			return *(&x+i);
		}

		inline Real& operator [] ( const size_t i )
		{
			assert( i < 3 );

			return *(&x+i);
		}
		/// Pointer accessor for direct copying
		inline Real* ptr()
		{
			return &x;
		}
		/// Pointer accessor for direct copying
		inline const Real* ptr() const
		{
			return &x;
		}

		inline Vec3& operator = ( const Vec3& rkVector )
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;

			return *this;
		}

		inline Vec3& operator = ( const Real fScaler )
		{
			x = fScaler;
			y = fScaler;
			z = fScaler;

			return *this;
		}

		inline bool operator == ( const Vec3& rkVector ) const
		{
			return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
		}

		inline bool operator != ( const Vec3& rkVector ) const
		{
			return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
		}

		// arithmetic operations
		inline Vec3 operator + ( const Vec3& rkVector ) const
		{
			return Vec3(
				x + rkVector.x,
				y + rkVector.y,
				z + rkVector.z);
		}

		inline Vec3 operator - ( const Vec3& rkVector ) const
		{
			return Vec3(
				x - rkVector.x,
				y - rkVector.y,
				z - rkVector.z);
		}

		inline Vec3 operator * ( const Real fScalar ) const
		{
			return Vec3(
				x * fScalar,
				y * fScalar,
				z * fScalar);
		}

		inline Vec3 operator * ( const Vec3& rhs) const
		{
			return Vec3(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		inline Vec3 operator / ( const Real fScalar ) const
		{
			assert( fScalar != 0.0 );

			Real fInv = 1.0f / fScalar;

			return Vec3(
				x * fInv,
				y * fInv,
				z * fInv);
		}

		inline Vec3 operator / ( const Vec3& rhs) const
		{
			return Vec3(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z);
		}

		inline const Vec3& operator + () const
		{
			return *this;
		}

		inline Vec3 operator - () const
		{
			return Vec3(-x, -y, -z);
		}

		// arithmetic updates
		inline Vec3& operator += ( const Vec3& rkVector )
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;

			return *this;
		}

		inline Vec3& operator -= ( const Vec3& rkVector )
		{
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;

			return *this;
		}

		inline Vec3& operator *= ( const Real fScalar )
		{
			x *= fScalar;
			y *= fScalar;
			z *= fScalar;
			return *this;
		}

		inline Vec3& operator *= ( const Vec3& rkVector )
		{
			x *= rkVector.x;
			y *= rkVector.y;
			z *= rkVector.z;

			return *this;
		}

		inline Vec3& operator /= ( const Real fScalar )
		{
			assert( fScalar != 0.0 );

			Real fInv = 1.0f / fScalar;

			x *= fInv;
			y *= fInv;
			z *= fInv;

			return *this;
		}

		inline Vec3& operator /= ( const Vec3& rkVector )
		{
			x /= rkVector.x;
			y /= rkVector.y;
			z /= rkVector.z;

			return *this;
		}

		inline void makeFloor( const Vec3& cmp )
		{
			if( cmp.x < x ) x = cmp.x;
			if( cmp.y < y ) y = cmp.y;
			if( cmp.z < z ) z = cmp.z;
		}

		inline void makeCeil( const Vec3& cmp )
		{
			if( cmp.x > x ) x = cmp.x;
			if( cmp.y > y ) y = cmp.y;
			if( cmp.z > z ) z = cmp.z;
		}

		inline Real length () const
		{
			return sqrt( x * x + y * y + z * z );
		}

		inline Real squaredLength () const
		{
			return x * x + y * y + z * z;
		}

		inline Real distance(const Vec3& rhs) const
		{
			return (*this - rhs).length();
		}

		inline Real squaredDistance(const Vec3& rhs) const
		{
			return (*this - rhs).squaredLength();
		}

		inline Real dot(const Vec3& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}

		inline Real normalise()
		{
			Real fLength = sqrt( x * x + y * y + z * z );

			// Will also work for zero-sized vectors, but will change nothing
			if ( fLength > 1e-08 )
			{
				Real fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}

			return fLength;
		}

		inline Vec3 cross( const Vec3& rkVector ) const
		{
			return Vec3(
				y * rkVector.z - z * rkVector.y,
				z * rkVector.x - x * rkVector.z,
				x * rkVector.y - y * rkVector.x);
		}

		inline Vec3 perpendicular(void) const
		{
			static const Real fSquareZero = (Real)(1e-06 * 1e-06);

			Vec3 perp = this->cross( Vec3::UNIT_X );

			// Check length
			if( perp.squaredLength() < fSquareZero )
			{
				/* This vector is the Y axis multiplied by a scalar, so we have
				to use another axis.
				*/
				perp = this->cross( Vec3::UNIT_Y );
			}
			perp.normalise();

			return perp;
		}

		inline bool isZeroLength(void) const
		{
			Real sqlen = (x * x) + (y * y) + (z * z);
			return (sqlen < (1e-06 * 1e-06));

		}

		inline Vec3 reflect(const Vec3& normal) const
		{
			return Vec3( *this - (normal * 2 * this->dot(normal)) );
		}

		static const Vec3 ZERO;
		static const Vec3 UNIT_X;
		static const Vec3 UNIT_Y;
		static const Vec3 UNIT_Z;
		static const Vec3 NEGATIVE_UNIT_X;
		static const Vec3 NEGATIVE_UNIT_Y;
		static const Vec3 NEGATIVE_UNIT_Z;
		static const Vec3 UNIT_SCALE;
	};

	class Vec4
	{
	public:
		Real x, y, z, w;

	public:
		inline Vec4()
		{
		}

		inline Vec4( const Real fX, const Real fY, const Real fZ, const Real fW )
			: x( fX ), y( fY ), z( fZ ), w( fW)
		{
		}

		inline explicit Vec4( const Real afCoordinate[4] )
			: x( afCoordinate[0] ),
			y( afCoordinate[1] ),
			z( afCoordinate[2] ),
			w( afCoordinate[3] )
		{
		}

		inline explicit Vec4( const int afCoordinate[4] )
		{
			x = (Real)afCoordinate[0];
			y = (Real)afCoordinate[1];
			z = (Real)afCoordinate[2];
			w = (Real)afCoordinate[3];
		}

		inline explicit Vec4( Real* const r )
			: x( r[0] ), y( r[1] ), z( r[2] ), w( r[3] )
		{
		}

		inline explicit Vec4( const Real scaler )
			: x( scaler )
			, y( scaler )
			, z( scaler )
			, w( scaler )
		{
		}

		inline explicit Vec4(const Vec3& rhs)
			: x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
		{
		}

		/** Exchange the contents of this vector with another. 
		*/
		inline void swap(Vec4& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}

		inline Real operator [] ( const size_t i ) const
		{
			assert( i < 4 );

			return *(&x+i);
		}

		inline Real& operator [] ( const size_t i )
		{
			assert( i < 4 );

			return *(&x+i);
		}

		/// Pointer accessor for direct copying
		inline Real* ptr()
		{
			return &x;
		}
		/// Pointer accessor for direct copying
		inline const Real* ptr() const
		{
			return &x;
		}

		/** Assigns the value of the other vector.
		@param
		rkVector The other vector
		*/
		inline Vec4& operator = ( const Vec4& rkVector )
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;
			w = rkVector.w;

			return *this;
		}

		inline Vec4& operator = ( const Real fScalar)
		{
			x = fScalar;
			y = fScalar;
			z = fScalar;
			w = fScalar;
			return *this;
		}

		inline bool operator == ( const Vec4& rkVector ) const
		{
			return ( x == rkVector.x &&
				y == rkVector.y &&
				z == rkVector.z &&
				w == rkVector.w );
		}

		inline bool operator != ( const Vec4& rkVector ) const
		{
			return ( x != rkVector.x ||
				y != rkVector.y ||
				z != rkVector.z ||
				w != rkVector.w );
		}

		inline Vec4& operator = (const Vec3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = 1.0f;
			return *this;
		}

		// arithmetic operations
		inline Vec4 operator + ( const Vec4& rkVector ) const
		{
			return Vec4(
				x + rkVector.x,
				y + rkVector.y,
				z + rkVector.z,
				w + rkVector.w);
		}

		inline Vec4 operator - ( const Vec4& rkVector ) const
		{
			return Vec4(
				x - rkVector.x,
				y - rkVector.y,
				z - rkVector.z,
				w - rkVector.w);
		}

		inline Vec4 operator * ( const Real fScalar ) const
		{
			return Vec4(
				x * fScalar,
				y * fScalar,
				z * fScalar,
				w * fScalar);
		}

		inline Vec4 operator * ( const Vec4& rhs) const
		{
			return Vec4(
				rhs.x * x,
				rhs.y * y,
				rhs.z * z,
				rhs.w * w);
		}

		inline Vec4 operator / ( const Real fScalar ) const
		{
			assert( fScalar != 0.0 );

			Real fInv = 1.0f / fScalar;

			return Vec4(
				x * fInv,
				y * fInv,
				z * fInv,
				w * fInv);
		}

		inline Vec4 operator / ( const Vec4& rhs) const
		{
			return Vec4(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z,
				w / rhs.w);
		}

		inline const Vec4& operator + () const
		{
			return *this;
		}

		inline Vec4 operator - () const
		{
			return Vec4(-x, -y, -z, -w);
		}

		// arithmetic updates
		inline Vec4& operator += ( const Vec4& rkVector )
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;
			w += rkVector.w;

			return *this;
		}

		inline Vec4& operator -= ( const Vec4& rkVector )
		{
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;
			w -= rkVector.w;

			return *this;
		}

		inline Vec4& operator *= ( const Real fScalar )
		{
			x *= fScalar;
			y *= fScalar;
			z *= fScalar;
			w *= fScalar;
			return *this;
		}

		inline Vec4& operator += ( const Real fScalar )
		{
			x += fScalar;
			y += fScalar;
			z += fScalar;
			w += fScalar;
			return *this;
		}

		inline Vec4& operator -= ( const Real fScalar )
		{
			x -= fScalar;
			y -= fScalar;
			z -= fScalar;
			w -= fScalar;
			return *this;
		}

		inline Vec4& operator *= ( const Vec4& rkVector )
		{
			x *= rkVector.x;
			y *= rkVector.y;
			z *= rkVector.z;
			w *= rkVector.w;

			return *this;
		}

		inline Vec4& operator /= ( const Real fScalar )
		{
			assert( fScalar != 0.0 );

			Real fInv = 1.0f / fScalar;

			x *= fInv;
			y *= fInv;
			z *= fInv;
			w *= fInv;

			return *this;
		}

		inline Vec4& operator /= ( const Vec4& rkVector )
		{
			x /= rkVector.x;
			y /= rkVector.y;
			z /= rkVector.z;
			w /= rkVector.w;

			return *this;
		}

		/** Calculates the dot (scalar) product of this vector with another.
		@param
		vec Vector with which to calculate the dot product (together
		with this one).
		@returns
		A float representing the dot product value.
		*/
		inline Real dot(const Vec4& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
		}
		/// Check whether this vector contains valid values

		// special
		static const Vec4 ZERO;
	};

}

#endif /* _TR_VEC_H_ */
