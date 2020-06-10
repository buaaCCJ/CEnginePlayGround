#ifndef CELL_RENDERER_RENDER_COMMAND_H
#define CELL_RENDERER_RENDER_COMMAND_H

#include <math/linear_algebra/vmath.h>

namespace Cell
{
    class Mesh;
    class Material;
	class SceneNode;
    /* 

      All render state required for submitting a render command.

    */
    struct RenderCommand
    {
		//temp
		SceneNode* Node=nullptr;
        math::mat4f Transform;
        math::mat4f PrevTransform;
        Mesh*      Mesh=nullptr;
        Material*  Material = nullptr;
        math::vec3f BoxMin;
        math::vec3f BoxMax;
    };

}

#endif