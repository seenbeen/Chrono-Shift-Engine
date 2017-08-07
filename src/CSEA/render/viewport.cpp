#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/camera.hpp>

#include <CSE/CSEA/render/viewport.hpp>

namespace CSEA { namespace Render {
    Viewport::Viewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        this->x = x;
        this->y = y;
        this->width = w;
        this->height = h;
        this->visible = true;
        this->boundScene = NULL;
        this->boundCamera = NULL;
    }

    Viewport::~Viewport() {}

    void Viewport::render(CSELL::Render::Renderer *renderer) {
        if (!this->visible) {
            return;
        }

        renderer->setViewport(this->x, this->y, this->width, this->height);
        renderer->clearDepth(1.0f);

        if (this->boundCamera != NULL && this->boundScene != NULL) {
            this->boundScene->render(this->boundCamera);
        } else if ((this->boundCamera != NULL && this->boundScene == NULL) ||
                   (this->boundCamera == NULL && this->boundScene != NULL)) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Viewport",
                             "Viewport has Scene or Camera attached but not the other!");
        }
    }

    void Viewport::bindCamera(Camera *cam) {
        this->boundCamera = cam;
    }

    void Viewport::bindScene(Scene *scene) {
        this->boundScene = scene;
    }

    void Viewport::setPosition(unsigned int x, unsigned int y) {
        this->x = x;
        this->y = y;
    }

    void Viewport::setDimensions(unsigned int w, unsigned int h) {
        this->width = w;
        this->height = h;
    }

    void Viewport::setVisible(bool visible) {
        this->visible = visible;
    }
}}
