#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace CSEA { namespace Render {
    bool Renderable::load(CSELL::Render::Renderer *renderer) {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Trying to load already loaded Renderable!");
            return false;
        }

        if (this->onLoad(renderer)) {
            this->isLoaded = true;
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                         "Failed to load OverlayRenderable!");
        return false;
    }

    bool Renderable::unload(CSELL::Render::Renderer *renderer) {
        if (!this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Renderable",
                             "Trying to unload already unloaded Renderable!");
            return false;
        }
        if (this->onUnload(renderer)) {
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
    }

    Renderable::~Renderable() {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - OverlayRenderable",
                             "Deleting OverlayRenderable which is still loaded!");
        }
    }
}}
