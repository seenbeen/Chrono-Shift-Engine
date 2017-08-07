#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>
#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Render {
    bool Renderable::load(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Trying to load already loaded Renderable!");
            return false;
        }

        if (this->onLoad(renderer, cacheManager)) {
            this->isLoaded = true;
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                         "Failed to load Renderable!");
        return false;
    }

    bool Renderable::unload(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) {
        if (!this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Trying to unload already unloaded Renderable!");
            return false;
        }
        if (this->onUnload(renderer, cacheManager)) {
            this->isLoaded = false;
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                         "Failed to unload Renderable!");
        return false;
    }

    void Renderable::update(double deltaTime) {
        if (this->isLoaded) {
            this->onUpdate(deltaTime);
        } else {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Trying update non-loaded Renderable!");
        }
    }

    void Renderable::render(Camera *camera) {
        if (this->isLoaded) {
            this->onRender(camera);
        } else {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Trying render non-loaded Renderable!");
        }
    }

    Renderable::Renderable() {
        this->isLoaded = false;
        this->boundScene = NULL;
        this->xform = CSELL::Math::Transform();
    }

    Renderable::~Renderable() {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Deleting Renderable which is still loaded!");
        }
    }

    void Renderable::setTransform(const CSELL::Math::Transform &xform) {
        this->xform = xform;
    }
}}
