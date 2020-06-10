#include "cube.h"

namespace Cell
{
    // --------------------------------------------------------------------------------------------
    Cube::Cube()
    {
        Positions = std::vector<math::vec3f> {
            math::vec3f(-0.5f, -0.5f, -0.5f),
            math::vec3f( 0.5f,  0.5f, -0.5f), 
            math::vec3f( 0.5f, -0.5f, -0.5f), 
            math::vec3f( 0.5f,  0.5f, -0.5f), 
            math::vec3f(-0.5f, -0.5f, -0.5f),
            math::vec3f(-0.5f,  0.5f, -0.5f),

            math::vec3f(-0.5f, -0.5f,  0.5f),
            math::vec3f( 0.5f, -0.5f,  0.5f),
            math::vec3f( 0.5f,  0.5f,  0.5f),
            math::vec3f( 0.5f,  0.5f,  0.5f), 
            math::vec3f(-0.5f,  0.5f,  0.5f),
            math::vec3f(-0.5f, -0.5f,  0.5f),

            math::vec3f(-0.5f,  0.5f,  0.5f),
            math::vec3f(-0.5f,  0.5f, -0.5f),
            math::vec3f(-0.5f, -0.5f, -0.5f),
            math::vec3f(-0.5f, -0.5f, -0.5f),
            math::vec3f(-0.5f, -0.5f,  0.5f),
            math::vec3f(-0.5f,  0.5f,  0.5f),

            math::vec3f( 0.5f,  0.5f,  0.5f), 
            math::vec3f( 0.5f, -0.5f, -0.5f), 
            math::vec3f( 0.5f,  0.5f, -0.5f), 
            math::vec3f( 0.5f, -0.5f, -0.5f), 
            math::vec3f( 0.5f,  0.5f,  0.5f), 
            math::vec3f( 0.5f, -0.5f,  0.5f), 

            math::vec3f(-0.5f, -0.5f, -0.5f),
            math::vec3f( 0.5f, -0.5f, -0.5f),
            math::vec3f( 0.5f, -0.5f,  0.5f),
            math::vec3f( 0.5f, -0.5f,  0.5f), 
            math::vec3f(-0.5f, -0.5f,  0.5f),
            math::vec3f(-0.5f, -0.5f, -0.5f),

            math::vec3f(-0.5f,  0.5f, -0.5f),
            math::vec3f( 0.5f,  0.5f,  0.5f), 
            math::vec3f( 0.5f,  0.5f, -0.5f), 
            math::vec3f( 0.5f,  0.5f,  0.5f), 
            math::vec3f(-0.5f,  0.5f, -0.5f),
            math::vec3f(-0.5f,  0.5f,  0.5f),
        };
        UV = std::vector<math::vec2f> {
            math::vec2f(0.0f, 0.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(0.0f, 0.0f),
            math::vec2f(0.0f, 1.0f),

            math::vec2f(0.0f, 0.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(0.0f, 1.0f),
            math::vec2f(0.0f, 0.0f),

            math::vec2f(1.0f, 0.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(0.0f, 1.0f),
            math::vec2f(0.0f, 1.0f),
            math::vec2f(0.0f, 0.0f),
            math::vec2f(1.0f, 0.0f),

            math::vec2f(1.0f, 0.0f),
            math::vec2f(0.0f, 1.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(0.0f, 1.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(0.0f, 0.0f),

            math::vec2f(0.0f, 1.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(0.0f, 0.0f),
            math::vec2f(0.0f, 1.0f),

            math::vec2f(0.0f, 1.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(1.0f, 1.0f),
            math::vec2f(1.0f, 0.0f),
            math::vec2f(0.0f, 1.0f),
            math::vec2f(0.0f, 0.0f),
        };
        Normals = std::vector<math::vec3f>{
            math::vec3f( 0.0f,  0.0f, -1.0f),
            math::vec3f( 0.0f,  0.0f, -1.0f),
            math::vec3f( 0.0f,  0.0f, -1.0f),
            math::vec3f( 0.0f,  0.0f, -1.0f),
            math::vec3f( 0.0f,  0.0f, -1.0f),
            math::vec3f( 0.0f,  0.0f, -1.0f),

            math::vec3f( 0.0f,  0.0f,  1.0f),
            math::vec3f( 0.0f,  0.0f,  1.0f),
            math::vec3f( 0.0f,  0.0f,  1.0f),
            math::vec3f( 0.0f,  0.0f,  1.0f),
            math::vec3f( 0.0f,  0.0f,  1.0f),
            math::vec3f( 0.0f,  0.0f,  1.0f),

            math::vec3f(-1.0f,  0.0f,  0.0f),
            math::vec3f(-1.0f,  0.0f,  0.0f),
            math::vec3f(-1.0f,  0.0f,  0.0f),
            math::vec3f(-1.0f,  0.0f,  0.0f),
            math::vec3f(-1.0f,  0.0f,  0.0f),
            math::vec3f(-1.0f,  0.0f,  0.0f),

            math::vec3f( 1.0f,  0.0f,  0.0f),
            math::vec3f( 1.0f,  0.0f,  0.0f),
            math::vec3f( 1.0f,  0.0f,  0.0f),
            math::vec3f( 1.0f,  0.0f,  0.0f),
            math::vec3f( 1.0f,  0.0f,  0.0f),
            math::vec3f( 1.0f,  0.0f,  0.0f),

            math::vec3f( 0.0f, -1.0f,  0.0f),
            math::vec3f( 0.0f, -1.0f,  0.0f),
            math::vec3f( 0.0f, -1.0f,  0.0f),
            math::vec3f( 0.0f, -1.0f,  0.0f),
            math::vec3f( 0.0f, -1.0f,  0.0f),
            math::vec3f( 0.0f, -1.0f,  0.0f),

            math::vec3f( 0.0f,  1.0f,  0.0f),
            math::vec3f( 0.0f,  1.0f,  0.0f),
            math::vec3f( 0.0f,  1.0f,  0.0f),
            math::vec3f( 0.0f,  1.0f,  0.0f),
            math::vec3f( 0.0f,  1.0f,  0.0f),
            math::vec3f( 0.0f,  1.0f,  0.0f),
        };

        Topology = TRIANGLES;
        Finalize();
    }
}