#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/render/overlayrenderable.hpp>
#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Render {
    bool OverlayRenderable::load(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                             "Trying to load already loaded OverlayRenderable!");
            return false;
        }

        if (this->onLoad(renderer, cacheManager)) {
            this->isLoaded = true;
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                         "Failed to load OverlayRenderable!");
        return false;
    }

    bool OverlayRenderable::unload(CSELL::Render::Renderer *renderer, CacheManager *cacheManager) {
        if (!this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                             "Trying to unload already unloaded OverlayRenderable!");
            return false;
        }
        if (this->onUnload(renderer, cacheManager)) {
            this->isLoaded = false;
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                         "Failed to unload OverlayRenderable!");
        return false;
    }

    void OverlayRenderable::update(double deltaTime) {
        if (this->isLoaded) {
            this->onUpdate(deltaTime);
        } else {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                             "Trying update non-loaded OverlayRenderable!");
        }
    }

    void OverlayRenderable::render(unsigned int viewportWidth, unsigned int viewportHeight) {
        if (this->isLoaded) {
            this->onRender(viewportWidth, viewportHeight);
        } else {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                             "Trying render non-loaded OverlayRenderable!");
        }
    }

    OverlayRenderable::OverlayRenderable() {
        this->isLoaded = false;
        this->boundOverlay = NULL;
    }

    OverlayRenderable::~OverlayRenderable() {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                             "Deleting OverlayRenderable which is still loaded!");
        }
    }
}}
