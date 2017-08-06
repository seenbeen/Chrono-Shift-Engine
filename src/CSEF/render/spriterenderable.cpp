#include <CSE/CSEF/render/spriterenderable.hpp>
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

namespace CSEF { namespace Render {
    SpriteRenderable::Animation::Animation(unsigned int nFrames, unsigned int *frames,
                                           int *originXs, int *originYs, float *delays) {
        this->nFrames = nFrames;
        this->frames = frames;
        this->originXs = originXs;
        this->originYs = originYs;
        this->delays = delays;
        this->animationLength = 0.0f;
        for (unsigned int i = 0; i < nFrames; i++) {
            this->animationLength += this->delays[i];
        }
    }

    SpriteRenderable::Animation::~Animation() {}

    void SpriteRenderable::Animation::getDataAtTime(float time, unsigned int &resultFrame,
                                                      int &originX, int &originY) {
        time = fmod(time, this->animationLength);

        for (unsigned int i = 0; i < this->nFrames; i++) {
            if (time <= 0) {
                resultFrame = this->frames[i];
                originX = this->originXs[i];
                originY = this->originYs[i];
                return;
            }
            time -= this->delays[i];
        }
        resultFrame = this->frames[this->nFrames - 1];
        originX = this->originXs[this->nFrames - 1];
        originY = this->originYs[this->nFrames - 1];
    }

    float SpriteRenderable::Animation::getAnimationLength() {
        return this->animationLength;
    }

    SpriteRenderable::SpriteRenderable() {
        this->spriteSheet = NULL;
        this->cutOuts = NULL;
        this->isInitialized = false;
    }

    SpriteRenderable::~SpriteRenderable() {
        if (this->animationMap.size()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "Not all animations have been erased on deletion.");
        }
    }

    bool SpriteRenderable::setup(CSELL::Render::Texture *spriteSheet, CSELL::Render::Mesh *cutOuts, CSELL::Render::ShaderProgram *shaderProgram) {
        if (spriteSheet == NULL || cutOuts == NULL || shaderProgram == NULL) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "Calling setup with NULL argument.");
            return false;
        }
        this->spriteSheet = spriteSheet;
        this->cutOuts = cutOuts;
        this->shaderProgram = shaderProgram;
        this->isInitialized = true;
        return true;
    }

    bool SpriteRenderable::addAnimation(const std::string &name, unsigned int nFrames, unsigned int *frames,
                                        int *originXs, int *originYs, float *delays) {
        std::map<std::string,Animation*>::iterator it = this->animationMap.find(name);
        if (it != this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "Trying to add existing animation.");
            return false;
        }
        this->animationMap[name] = new Animation(nFrames, frames, originXs, originYs, delays);
        return true;
    }

    bool SpriteRenderable::deleteAnimation(const std::string &name) {
        std::map<std::string,Animation*>::iterator it = this->animationMap.find(name);
        if (it == this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN,  CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "Trying to delete non-existent animation.");
            return false;
        }

        delete it->second;
        this->animationMap.erase(it);

        return true;
    }

    void SpriteRenderable::onUpdate(double deltaTime) {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "In Method: Update. SpriteRenderable has not been setup.");
            return;
        } else if (this->currentAnimation == NULL) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "In Method: Update. Current animation is NULL.");
            return;
        }
        this->currentTime = fmod(this->currentTime + deltaTime, this->currentAnimation->getAnimationLength());
    }

    void SpriteRenderable::onRender(CSEA::Render::Camera *camera) {
        if (!this->isInitialized) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "In Method: Render. SpriteRenderable has not been setup.");
            return;
        } else if (this->currentAnimation == NULL) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "In Method: Render. Current animation is NULL.");
            return;
        }

        unsigned int frame;
        int ox, oy;

        this->currentAnimation->getDataAtTime(this->currentTime, frame, ox, oy);

        glm::mat4 tempMat;

        this->shaderProgram->useShaderProgram();

        CSELL::Math::Vector3f &pos = this->xform.position;

        tempMat = glm::translate(tempMat, glm::vec3(pos.x + ox, pos.y + oy, pos.z));

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
        std::map<std::string,SpriteRenderable::Animation*>::iterator it = this->animationMap.find(name);
        if (it == this->animationMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEF, "Render - SpriteRenderable",
                             "Trying to set Animation to unknown animation \"" + name + "\".");
            return false;
        }
        this->currentTime = 0.0f;
        this->currentAnimation = it->second;
        return true;
    }

    bool SpriteRenderable::setCurrentAnimationTime(float time) {
        this->currentTime = time;
        return true;
    }

    float SpriteRenderable::getCurrentAnimationTime() {
        return this->currentTime;
    }
}}
