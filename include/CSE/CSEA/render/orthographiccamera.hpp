#ifndef CSEA_RENDER_ORTHOGRAPHICCAMERA_HPP
#define CSEA_RENDER_ORTHOGRAPHICCAMERA_HPP

#include <lib/glm/glm.hpp>

#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    class OrthographicCamera : public Camera {
        float l,r,d,u,n,f; // clipping planes for frustum

    protected:
        void updateViewMatrix(glm::mat4 &mat);
        void updateProjMatrix(glm::mat4 &mat);

    public:
        OrthographicCamera(float l, float r, float d, float u, float n, float f);
        ~OrthographicCamera();

        void resizeFrustum(float l, float r, float d, float u, float n, float f);

        void getFrustumBounds(CSELL::Math::Vector3f &NBL, CSELL::Math::Vector3f &NBR,
                              CSELL::Math::Vector3f &NTL, CSELL::Math::Vector3f &NTR,
                              CSELL::Math::Vector3f &FBL, CSELL::Math::Vector3f &FBR,
                              CSELL::Math::Vector3f &FTL, CSELL::Math::Vector3f &FTR);
    };
}}
#endif

