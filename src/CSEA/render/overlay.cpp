#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/render/renderer.hpp>
#include <CSE/CSEA/render/overlay.hpp>
#include <CSE/CSEA/render/overlayrenderable.hpp>

namespace CSEA { namespace Render {
    Overlay::Overlay() {
        this->isLoaded = false;
    }

    Overlay::~Overlay() {
        if (this->renderables.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                             "Not all OverlayRenderables have been detached from Overlay on deletion!");
        }
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            (*it)->boundOverlay = NULL;
        }
    }

    void Overlay::update(double deltaTime) {
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            (*it)->update(deltaTime);
        }
    }

    void Overlay::render(unsigned int viewportWidth, unsigned int viewportHeight) {
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            (*it)->render(viewportWidth, viewportHeight);
        }
    }

    void Overlay::onLoad() {
        if (this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                             "Trying to load already loaded overlay!");
            return;
        }
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            CSEA::Render::Renderer::loadOverlayRenderable(*it);
        }
        this->isLoaded = true;
    }

    void Overlay::onUnload() {
        if (!this->isLoaded) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                             "Trying to unload unloaded overlay!");
            return;
        }
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); ++it) {
            CSEA::Render::Renderer::unloadOverlayRenderable(*it);
        }
        this->isLoaded = false;
    }

    bool Overlay::addOverlayRenderable(OverlayRenderable *overRend) {
        if (overRend->boundOverlay != NULL) {
            if (overRend->boundOverlay == this) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                                 "Trying to add Overlay Renderable already bound to this Overlay!");
            } else {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                                 "Trying to add Overlay Renderable already bound to an Overlay!");
            }
            return false;
        }
        overRend->boundOverlay = this;
        this->renderables.insert(overRend);
        if (this->isLoaded) {
            CSEA::Render::Renderer::loadOverlayRenderable(overRend);
        }
        return true;
    }

    bool Overlay::removeOverlayRenderable(OverlayRenderable *overRend) {
        if (overRend->boundOverlay != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                             "Trying to remove Overlay Renderable not bound to Overlay!");
            return false;
        }
        overRend->boundOverlay = NULL;
        if (this->isLoaded) {
            CSEA::Render::Renderer::unloadOverlayRenderable(overRend);
        }
        this->renderables.erase(this->renderables.find(overRend));
        return true;
    }
}}

