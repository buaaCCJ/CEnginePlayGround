#ifndef CELL_CAMERA_FRUSTUM_H
#define CELL_CAMERA_FRUSTUM_H

#include <math/linear_algebra/vmath.h>

namespace Cell
{
    class Camera;

    /* 
        
      Data container for the 3D plane equation variables in Cartesian space. A plane equation can be
      defined by its Normal (perpendicular to the plane) and a distance value D obtained from any
      point on the plane itself (projected onto the normal vector).

    */
    struct FrustumPlane
    {
        math::vec3f Normal;
        float      D;

        void SetNormalD(math::vec3f normal, math::vec3f point)
        {
            Normal =normal;
			Normal.normalize();
           // D      = -math::dot(Normal, point);
			D = -Normal.dotProduct(point);

        }

        float Distance(math::vec3f point)
        {
            return Normal.dotProduct(point) + D;
        }
    };


    /*

      Container object managing all 6 camera frustum planes as calculated from any Camera object.

      The CameraFrustum allows to quickly determine (using simple collision primitives like point,
      sphere, box) whether an object is within the frustum (or crossing the frustum's edge(s)). 
      This gives us the option to significantly reduce draw calls for objects that aren't visible
      anyways. Note that the frustum needs to be re-calculated every frame.

    */
    class CameraFrustum
    {
    public:
       /* union
        {*/
            FrustumPlane Planes[6];
        /*    struct
            {*/
              /*  FrustumPlane Left;
                FrustumPlane Right;
                FrustumPlane Top;
                FrustumPlane Bottom;
                FrustumPlane Near;
                FrustumPlane Far;*/
           // };
       /* };*/

    public:
        CameraFrustum() { } // NOTE(Joey): why do I need to define a constructor here? (otherwise I get deleted constructor error) LOOK IT UP!

        void Update(Camera* camera);

        bool Intersect(math::vec3f point);
        bool Intersect(math::vec3f point, float radius);
        bool Intersect(math::vec3f boxMin, math::vec3f boxMax);
		
    };
}
#endif