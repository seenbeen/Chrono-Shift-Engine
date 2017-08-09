#include <CSE/CSEA/render/orthographiccamera.hpp>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

namespace CSEA { namespace Render {
    void OrthographicCamera::updateViewMatrix(glm::mat4 &view) {
        glm::vec3 cPos,tPos,up;

        cPos = glm::vec3(this->position.x, this->position.y, this->position.z);

        if (this->directionAxis.x != 0.0f || this->directionAxis.y != 0.0f) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OrthographicCamera",
                             "Not looking directly down the Z axis unsupported, undefined behavior may occur.");
        }

        CSELL::Math::Vector3f temp = this->position + this->directionAxis;

        tPos = glm::vec3(temp.x, temp.y, temp.z);

        up = glm::vec3(this->upAxis.x, this->upAxis.y, this->upAxis.z);
        if (this->upAxis.z != 0.0f) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OrthographicCamera",
                             "Rotation into Z unsupported, undefined behavior may occur.");
        }
        view = glm::lookAt(cPos,tPos,up);
    }

    void OrthographicCamera::updateProjMatrix(glm::mat4 &proj) {
        proj = glm::ortho(this->l, this->r, this->d, this->u, this->n, this->f);
    }

    void OrthographicCamera::getFrustumBounds(CSELL::Math::Vector3f &NBL, CSELL::Math::Vector3f &NBR,
                                              CSELL::Math::Vector3f &NTL, CSELL::Math::Vector3f &NTR,
                                              CSELL::Math::Vector3f &FBL, CSELL::Math::Vector3f &FBR,
                                              CSELL::Math::Vector3f &FTL, CSELL::Math::Vector3f &FTR) {
        NBL.x = this->l;
        NBL.y = this->d;
        NBL.z = this->n;

        NBR.x = this->r;
        NBR.y = this->d;
        NBR.z = this->n;

        NTL.x = this->l;
        NTL.y = this->u;
        NTL.z = this->n;

        NTR.x = this->r;
        NTR.y = this->u;
        NTR.z = this->n;

        FBL.x = this->l;
        FBL.y = this->d;
        FBL.z = this->f;

        FBR.x = this->r;
        FBR.y = this->d;
        FBR.z = this->f;

        FTL.x = this->l;
        FTL.y = this->u;
        FTL.z = this->f;

        FTR.x = this->r;
        FTR.y = this->u;
        FTR.z = this->f;
    }

    OrthographicCamera::OrthographicCamera(float l, float r, float d, float u, float n, float f) {
        this->l = l;
        this->r = r;
        this->d = d;
        this->u = u;
        this->n = n;
        this->f = f;
        this->directionAxis = CSELL::Math::Vector3f(0.0f, 0.0f, -1.0f);
        this->position = CSELL::Math::Vector3f(0.0f, 0.0f, 0.0f);
        this->upAxis = CSELL::Math::Vector3f(0.0f, 1.0f, 0.0f);
    }

    OrthographicCamera::~OrthographicCamera() {}

    void OrthographicCamera::resizeFrustum(float l, float r, float d, float u, float n, float f) {
        this->l = l;
        this->r = r;
        this->d = d;
        this->u = u;
        this->n = n;
        this->f = f;
        this->updateProjectionProperties();
    }
}}
