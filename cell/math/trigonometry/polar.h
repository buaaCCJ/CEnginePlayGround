#ifndef MATH_TRIGONOMETRY_POLAR_H
#define MATH_TRIGONOMETRY_POLAR_H

#include "../linear_algebra/vmath.h"

namespace math
{
    /* NOTE(Joey): 

      Polar coordinates w/ relevant conversion for
      converting to and from cartesian coordinates.

    */
    struct polar
    {
        float r;     // NOTE(Joey): distance coordinate from origin.
        float theta; // NOTE(Joey): counter-clockwise rotation from x-axis.

        polar(float r, float theta);
        // NOTE(Joey): convert from cartesian.
        polar(vec2f cartesian); 

        // NOTE(Joey): convert to cartesian.
        vec2f ToCartesian();
    };
}

#endif