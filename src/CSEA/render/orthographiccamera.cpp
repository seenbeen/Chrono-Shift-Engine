#include <CSE/CSEA/render/orthographiccamera.hpp>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

namespace CSEA { namespace Render {
    void OrthographicCamera::updateViewMatrix(glm::mat4 &view) {
        glm::vec3 cPos,tPos,up;

        cPos = glm::vec3(this->position.x, this->position.y, this->position.z);

        CSELL::Math::Vector3f temp = this->position+this->directionAxis;

        tPos = glm::vec3(temp.x, temp.y, temp.z);

        up = glm::vec3(this->upAxis.x,this->upAxis.y,this->upAxis.z);

        //view = glm::lookAt(cPos, tPos, up);
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Render - OrthographicCamera", "Updated View");
    }

    void OrthographicCamera::updateProjMatrix(glm::mat4 &proj) {
        proj = glm::ortho(this->l, this->r, this->d, this->u, this->n, this->f);
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Render - OrthographicCamera", "Updated Proj");
    }

    OrthographicCamera::OrthographicCamera(float l, float r, float d, float u, float n, float f) {
        this->l = l;
        this->r = r;
        this->d = d;
        this->u = u;
        this->n = n;
        this->f = f;
    }

    OrthographicCamera::~OrthographicCamera() {}
}}
