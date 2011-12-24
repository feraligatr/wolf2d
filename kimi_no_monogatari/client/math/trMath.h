#ifndef _TR_MATH_H_
#define _TR_MATH_H_

#include <math.h>

namespace tree
{

	/* copy ogre's implementation and delete most operation for simplicity and integration with other library. */

	typedef float Real;

	class Math
	{
	public:
		static const Real POS_INFINITY;
		static const Real NEG_INFINITY;
		static const Real PI;
		static const Real TWO_PI;
		static const Real HALF_PI;
		static const Real fDeg2Rad;
		static const Real fRad2Deg;
		static const Real LOG2;

		inline static Real sqrt(Real r)
		{
			return ::sqrt(r);
		}

		inline static Real invSqrt(Real r)
		{
			return 1.0 / ::sqrt(r);
		}

		inline static Real sin(Real r)
		{
			return ::sin(r);
		}

		inline static Real cos(Real r)
		{
			return ::cos(r);
		}

		inline static Real acos(Real r)
		{
			return ::acos(r);
		}

		inline static Real abs(Real r)
		{
			return ::abs(r);
		}

		inline static bool realEqual(Real a, Real b, Real tolerance = std::numeric_limits<Real>::epsilon())
		{
			if (fabs(b-a) <= tolerance)
				return true;
			else
				return false;
		}
	};

}

#include "trQuat.h"
#include "trVec.h"
#include "trMat3.h"
#include "trMat4.h"

#endif /* _TR_MATH_H_ */
