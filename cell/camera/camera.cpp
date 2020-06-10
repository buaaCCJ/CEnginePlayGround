#include "camera.h"
#include <math.h>

namespace Cell
{
    // --------------------------------------------------------------------------------------------
    Camera::Camera()
    {

    }
    // --------------------------------------------------------------------------------------------
    Camera::Camera(math::vec3f position, math::vec3f forward, math::vec3f up) : Position(position), Forward(forward), Up(up)
    {
        UpdateView();
    }
    // --------------------------------------------------------------------------------------------
    void Camera::Update(float dt)
    {
        Frustum.Update(this);
    }
    // --------------------------------------------------------------------------------------------
    void Camera::SetPerspective(float fov, float aspect, float near, float far)
    {
        Perspective = true;
		//Note(ChenC)
		//fov is degree

        Projection = math::mat4f::createPerspective(fov, aspect, near, far);
        FOV    = fov;
        Aspect = aspect;
        Near   = near;
        Far    = far;
    }
    // --------------------------------------------------------------------------------------------
    void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
    {
        Perspective = false;
        Projection = math::mat4f::createOrtho(left, right, top, bottom, near, far);
        Near = near;
        Far  = far;
    }
    // --------------------------------------------------------------------------------------------
    void Camera::UpdateView()
    {
        View = math::mat4f::createLookAt(Position, Position + Forward, Up);
    }
    // --------------------------------------------------------------------------------------------
    float Camera::FrustumHeightAtDistance(float distance)
    {
        if (Perspective)
        {
             return 2.0f * distance * tanf(math::Deg2Rad(FOV * 0.5));
        }
        else
        {
            return Frustum.Planes[2].D;
        }
    }
    // --------------------------------------------------------------------------------------------
    float Camera::DistanceAtFrustumHeight(float frustumHeight)
    {
        if (Perspective)
        {
            return frustumHeight * 0.5f / tanf(math::Deg2Rad(FOV * 0.5f));
        }
        else
        {
           // return Frustum.Near.D;
		    return Frustum.Planes[4].D;

        }
    }

};