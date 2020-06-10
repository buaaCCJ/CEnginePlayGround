#ifndef CELL_LIGHTING_DIRECTIONAL_LIGHT_H
#define CELL_LIGHTING_DIRECTIONAL_LIGHT_H

#include <math/linear_algebra/vmath.h>



namespace Cell
{
    class RenderTarget;

    /*

      Light container object for any 3D directional light source. Directional light types support
      shadow casting, holding a reference to the RenderTarget (and the relevant light space view 
      projection matrix) used for its shadow map generation.

    */
    class DirectionalLight
    {
    public:
        math::vec3f Direction = math::vec3f(0.0f);
        math::vec3f Color     = math::vec3f(1.0f);
        float Intensity      = 1.0f;

        bool CastShadows = true;
        RenderTarget* ShadowMapRT=nullptr;
        math::mat4f    LightSpaceViewProjection;
    };
}

#endif