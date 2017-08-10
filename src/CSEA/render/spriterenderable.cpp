#include <CSE/CSEA/render/spriterenderable.hpp>
#include <math.h>
#include <map>
#include <string>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSEA/render/camera.hpp>

#include <CSE/CSEA/asset/spriteanimationset.hpp>

namespace CSEA { namespace Render {
    SpriteRenderable::SpriteRenderable() {
        this->animSet = NULL;
        this->spriteSheet = NULL;
        this->cutOuts = NULL;
        this->shaderProgram = NULL;
        this->isInitialized = false;
        this->currentAnimation = "NO_ANIMATION_SET";
        this->currentTime = -1.0f;
        this->currentAnimationLength = -1.0f;
    }

    SpriteRenderable::~SpriteRenderable() {}

    bool SpriteRenderable::setup(CSEA::Assets::SpriteAnimationSet *animSet, CSELL::Render::Texture *spriteSheet,
                                 CSELL::Render::Mesh *cutOuts, CSELL::Render::ShaderProgram *shaderProgram) {
        if (animSet == NULL || spriteSheet == NULL || cutOuts == NULL || shaderProgram == NULL) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: setup. No arguments may be NULL.");
            return false;
        }
        this->animSet = animSet;
        this->spriteSheet = spriteSheet;
        this->cutOuts = cutOuts;
        this->shaderProgram = shaderProgram;
        this->isInitialized = true;
        return true;
    }

    void SpriteRenderable::onUpdate(double deltaTime) {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: Update. SpriteRenderable has not been setup.");
            return;
        }
        this->currentTime = fmod(this->currentTime + deltaTime, this->currentAnimationLength);
    }

    void SpriteRenderable::onRender(CSEA::Render::Camera *camera) {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: Render. SpriteRenderable has not been setup.");
            return;
        }

        unsigned int frame;
        int ox, oy;

        if (!this->animSet->getAnimationDataAtTime(this->currentAnimation, this->currentTime, frame, ox, oy)) {
            return;
        }

        glm::mat4 tempMat;

        this->shaderProgram->useShaderProgram();

        CSELL::Math::Transform &xform = *this->xform;

        tempMat = glm::translate(tempMat, glm::vec3(xform.position.x, xform.position.y, xform.position.z));

        if (xform.scale.z != 1.0f) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "Ignoring scaling factor on Z axis as sprite has no depth.");
        }
        tempMat = glm::scale(tempMat, glm::vec3(xform.scale.x, xform.scale.y, 1.0f));

        if (xform.orientation.x != 0.0f || xform.orientation.y != 0) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "Sprite's orientation about x and y axes are not 0 - will only honor z component.");
        }
        tempMat = glm::rotate(tempMat, glm::radians(xform.orientation.z), glm::vec3(0.0f,0.0f,1.0f));

        tempMat = glm::translate(tempMat, glm::vec3(-ox, -oy, 0.0f));

        this->shaderProgram->setMat4f("model", glm::value_ptr(tempMat));

        camera->getViewMatrix(tempMat);

        this->shaderProgram->setMat4f("view", glm::value_ptr(tempMat));

        camera->getProjMatrix(tempMat);

        this->shaderProgram->setMat4f("projection",glm::value_ptr(tempMat));

        this->shaderProgram->setInt("spriteSheet", 0);
        this->spriteSheet->useActiveTexture(0);
        this->cutOuts->useMesh();

        this->cutOuts->renderMesh(6*frame,6*(frame+1));
    }

    bool SpriteRenderable::setCurrentAnimation(const std::string &name) {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: setCurrentAnimation. SpriteRenderable has not been setup.");
            return false;
        }
        float tempTime = 0.0f;
        if (!this->animSet->getAnimationLength(name, tempTime)) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: setCurrentAnimation. Unknown \"" + name + "\".");
            return false;
        }

        if (this->currentAnimation == name) {
            return true;
        }

        this->currentAnimationLength = tempTime;
        this->currentTime = 0.0f;
        this->currentAnimation = name;
        return true;
    }

    std::string SpriteRenderable::getCurrentAnimation() {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: getCurrentAnimation. SpriteRenderable has not been setup.");
            return "";
        }
        return this->currentAnimation;
    }

    bool SpriteRenderable::setCurrentAnimationTime(float time) {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: setCurrentAnimationTime. SpriteRenderable has not been setup.");
            return false;
        }
        this->currentTime = fmod(time, this->currentAnimationLength);
        return true;
    }

    float SpriteRenderable::getCurrentAnimationTime() {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - SpriteRenderable",
                             "In: getCurrentAnimationTime. SpriteRenderable has not been setup.");
            return -1.0f;
        }
        return this->currentTime;
    }
}}
