#include "spherical.h"

#include <math.h>

namespace math
{
	// NOTE(Nabil/htmlboss): using an initializer list is faster than doing: this->rho = Rho, etc.
    spherical::spherical(const float Rho, const float Phi, const float Theta) : rho(Rho), phi(Phi), theta(Theta) 
	{

    }

    spherical::spherical(const vec3f& cartesian)
    {
        rho   = cartesian.length();
		auto temp = vec2f(cartesian.x, cartesian.y);
		phi   = atan2(temp.length(), cartesian.z);

        //phi   = atan2(length(cartesian.xy), cartesian.z);
        theta = atan2(cartesian.y, cartesian.x);
    }

    vec3f spherical::ToCartesian() const
    {
        return vec3f(
            rho * sin(phi) * cos(theta), // NOTE(Joey); project phi onto xy plane and then polar coordinate conversion (r*cos(theta))
            rho * sin(phi) * sin(theta), // NOTE(Joey); project phi onto xy plane and then polar coordinate conversion (r*sin(theta))
            rho * cos(phi)             
        );
    }

} // namespace math