#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/render/overlay.hpp>
#include <CSE/CSEA/render/overlayrenderable.hpp>

namespace CSEA { namespace Render {
    Overlay::Overlay() {}

    Overlay::~Overlay() {
        if (this->renderables.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                             "Not all OverlayRenderables have been detached from Overlay on deletion!");
        }
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); it++) {
            (*it)->boundOverlay = NULL;
        }
    }

    void Overlay::update(double deltaTime) {
        if (this->isActive) {
            std::set<OverlayRenderable*>::iterator it;
            for (it = this->renderables.begin(); it != this->renderables.end(); it++) {
                (*it)->update(deltaTime);
            }
        }
    }

    void Overlay::render(unsigned int viewportWidth, unsigned int viewportHeight) {
        std::set<OverlayRenderable*>::iterator it;
        for (it = this->renderables.begin(); it != this->renderables.end(); it++) {
            (*it)->render(viewportWidth, viewportHeight);
        }
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
        return true;
    }

    bool Overlay::removeOverlayRenderable(OverlayRenderable *overRend) {
        if (overRend->boundOverlay != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Overlay",
                             "Trying to remove Overlay Renderable not bound to Overlay!");
            return false;
        }
        overRend->boundOverlay = NULL;
        this->renderables.erase(this->renderables.find(overRend));
        return true;
    }

    void Overlay::setIsActive(bool isActive) {
        this->isActive = isActive;
    }

    bool Overlay::getIsActive() {
        return this->isActive;
    }
}}

