#ifndef CSEA_RENDER_CAMERA_HPP
#define CSEA_RENDER_CAMERA_HPP
#include <lib/glm/glm.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

namespace CSEA { namespace Render {
    class Camera {
        bool isProjDirty, isViewDirty; // the matrices in this camera need updating

        glm::mat4 projMatrix, viewMatrix;

    protected:
        void updateProjectionProperties();
        CSELL::Math::Vector3f position, upAxis, directionAxis;

        virtual void updateViewMatrix(glm::mat4 &view) = 0;
        virtual void updateProjMatrix(glm::mat4 &proj) = 0;
        Camera();
        virtual ~Camera();
    public:
        void getViewMatrix(glm::mat4 &view);
        void getProjMatrix(glm::mat4 &proj);

        void setPosition(const CSELL::Math::Vector3f &position);
        void getPosition(CSELL::Math::Vector3f &position);

        void setOrientation(const CSELL::Math::Vector3f &upAxis, const CSELL::Math::Vector3f &directionAxis);
        void getOrientation(CSELL::Math::Vector3f &upAxis, CSELL::Math::Vector3f &directionAxis);
    };
}}
#endif
