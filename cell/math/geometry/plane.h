#ifndef MATH_GEOMETRY_PLANE_H
#define MATH_GEOMETRY_PLANE_H

#include "../linear_algebra/vmath.h"
namespace math
{
	/* NOTE(Joey):

	  Plane as deducted by the generalized plane equation.
	  Only defined in 3-dimensional space.

	*/
	struct plane
	{
		vec3f Normal;
		float Distance;

		plane(const float a, const float b, const float c, const float d);
		plane(const vec3f& normal, const vec3f& point);
	};
} // namespace math

#endif