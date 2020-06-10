#ifndef CELL_MATH_H
#define CELL_MATH_H

// todo: rename math.h, might not be the best name, google.

// NOTE(Joey): linear algebra
#include "linear_algebra/vmath.h"

// NOTE(Joey): trigonometry
#include "trigonometry/conversions.h"
#include "trigonometry/polar.h"
#include "trigonometry/spherical.h"
#include "assimp/matrix4x4.h"
// NOTE(Joey): common operations
#include "common.h"
namespace math{

	class MathHelper
	{
	public:
		static float clamp01(const float t)
		{
			if (t < 0)
				return 0;
			if (t > 1)
				return 1;
			return t;
		}
	};
}


#endif