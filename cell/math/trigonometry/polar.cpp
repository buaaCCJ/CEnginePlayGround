#include "polar.h"

#include <math.h>

#include "math/cmath.h"

namespace math
{
    polar::polar(float r, float theta)
    {
        this->r     = r;
        this->theta = theta;
    }

    polar::polar(vec2f cartesian)
    {
        r     = cartesian.length(); // NOTE(Joey): length of vec2(x, y).
        theta = atan2(cartesian.y, cartesian.x);
    }

    vec2f polar::ToCartesian()
    {
        return vec2f(r * cos(theta), r * sin(theta));
    }
}