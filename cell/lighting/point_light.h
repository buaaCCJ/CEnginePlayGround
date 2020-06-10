#ifndef CELL_LIGHTING_POINT_LIGHT_H
#define CELL_LIGHTING_POINT_LIGHT_H

#include <math/linear_algebra/vmath.h>

#include "../shading/material.h"
#include "../mesh/sphere.h"

namespace Cell
{
    /*

      Light container object for any 3D point light source. Point lights range are solely 
      determined by a radius value which is used for their frustum culling and attenuation
      properties. Attenuation is calculated based on a slightly tweaked point light attenuation
      equation derived by Epic Games (for use in UE4).

    */
    class PointLight
    {
    public:
        math::vec3f Position   = math::vec3f(0.0f);
        math::vec3f Color      = math::vec3f(1.0f);
        float      Intensity  = 1.0f;
        float      Radius     = 1.0f;
        bool       Visible    = true;
        bool       RenderMesh = false;
    };
}
#endif