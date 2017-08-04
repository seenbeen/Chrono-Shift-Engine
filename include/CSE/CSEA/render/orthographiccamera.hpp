#ifndef CSEA_RENDER_ORTHOGRAPHICCAMERA_HPP
#define CSEA_RENDER_ORTHOGRAPHICCAMERA_HPP

#include <lib/glm/glm.hpp>

#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    class OrthographicCamera : public Camera {
        float l,r,d,u,n,f; // clipping planes for frustum
    public:
        void updateViewMatrix(glm::mat4 &mat);
        void updateProjMatrix(glm::mat4 &mat);

        OrthographicCamera(float l, float r, float d, float u, float n, float f);
        ~OrthographicCamera();
    };
}}
#endif
