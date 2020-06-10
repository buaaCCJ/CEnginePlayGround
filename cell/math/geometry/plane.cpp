#include "plane.h"

#include "../linear_algebra/vmath.h"

namespace math
{
    plane::plane(const float a, const float b, const float c, const float d)
    {
        Normal.x = a;
        Normal.y = b;
        Normal.z = c;
        Distance = d;
    }

    plane::plane(const vec3f& normal, const vec3f& point)
    {
        Normal   = normal;
       // Distance = -dot(normal, point);
		Distance = normal.dotProduct(point);
    }
} // namespace math