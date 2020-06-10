#ifndef CELL_RENDERER_PBR_CAPTURE_H
#define CELL_RENDERER_PBR_CAPTURE_H

#include "../shading/texture_cube.h"

#include <math/linear_algebra/vmath.h>

namespace Cell
{
    /* 

      Container object for holding all per-environment specific pre-computed PBR data.

    */
    struct PBRCapture
    {
        TextureCube* Irradiance  = nullptr;
        TextureCube* Prefiltered = nullptr;
		TextureCube* originSkyBox = nullptr;
        math::vec3f Position;
        float      Radius;
    };
}

#endif