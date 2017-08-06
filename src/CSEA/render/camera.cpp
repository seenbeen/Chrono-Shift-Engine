#include <lib/glm/glm.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    Camera::Camera() {
        this->isViewDirty = true;
        this->isProjDirty = true;
    }

    Camera::~Camera() {}

    void Camera::getViewMatrix(glm::mat4 &view) {
        if (this->isViewDirty) {
            this->updateViewMatrix(this->viewMatrix);
            this->isViewDirty = false;
        }
        view = this->viewMatrix;
    }

    void Camera::getProjMatrix(glm::mat4 &proj) {
        if (this->isProjDirty) {
            this->updateProjMatrix(this->projMatrix);
            this->isProjDirty = false;
        }
        proj = this->projMatrix;
    }

    void Camera::setPosition(const CSELL::Math::Vector3f &position) {
        this->position = position;
        this->isViewDirty = true;
    }

    void Camera::getPosition(CSELL::Math::Vector3f &position) {
        position = this->position;
    }

    void Camera::setOrientation(const CSELL::Math::Vector3f &upAxis, const CSELL::Math::Vector3f &directionAxis) {
        this->upAxis = upAxis;
        this->directionAxis = directionAxis;
        this->isViewDirty = true;
    }

    void Camera::getOrientation(CSELL::Math::Vector3f &upAxis, CSELL::Math::Vector3f &directionAxis) {
        upAxis = this->upAxis;
        directionAxis = this->directionAxis;
    }

    void Camera::updateProjectionProperties() {
        this->isProjDirty = true;
    }
}}
