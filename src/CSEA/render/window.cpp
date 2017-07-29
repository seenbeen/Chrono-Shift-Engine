#include <string>
#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/window.hpp>

#include <CSE/CSELL/render/rendererimple.hpp>

#include <CSE/CSEA/render/window.hpp>
#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/overlay.hpp>
#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/overlayrenderable.hpp>

namespace CSEA { namespace Render {
    Window::Window(CSELL::Core::Window *window, CSELL::Render::RendererImple *rImple, Window::Settings &settings) {
        this->successfulInit = false;

        CSELL::Core::Window::Settings csellWinSettings;
        csellWinSettings.width = settings.width;
        csellWinSettings.height = settings.height;
        csellWinSettings.title = settings.windowTitle;
        csellWinSettings.resizeable = settings.isResizeable;
        // don't care about full screen... (might do so at some point)

        if (window->initialize(csellWinSettings)) {
            this->renderer = CSELL::Render::Renderer::newRenderer(window, rImple);
            this->successfulInit = true;
        }
    }

    Window::~Window() {
        std::set<Scene*>::iterator sceneIt;
        std::set<Overlay*>::iterator overIt;
        std::set<Viewport*>::iterator viewIt;

        if (this->scenes.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Window",
                               "Not all scenes deleted.");
        }

        if (this->overlays.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Window",
                               "Not all overlays deleted.");
        }

        if (this->viewports.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - Window",
                               "Not all viewports deleted.");
        }

        // delete scenes
        for (sceneIt = this->scenes.begin(); sceneIt != this->scenes.end(); sceneIt++) {
            delete (*sceneIt);
        }

        // delete overlays
        for (overIt = this->overlays.begin(); overIt != this->overlays.end(); overIt++){
            delete (*overIt);
        }

        // delete viewports
        for (viewIt = this->viewports.begin(); viewIt != this->viewports.end(); viewIt++) {
            delete (*viewIt);
        }

        delete this->renderer;
    }

    void Window::update(double deltaTime) {
        std::set<Scene*>::iterator sceneIt;
        std::set<Overlay*>::iterator overIt;
        std::set<Viewport*>::iterator viewIt;

        // update active scenes
        for (sceneIt = this->scenes.begin(); sceneIt != this->scenes.end(); sceneIt++) {
            (*sceneIt)->update(deltaTime);
        }

        // update active overlays
        for (overIt = this->overlays.begin(); overIt != this->overlays.end(); overIt++){
            (*overIt)->update(deltaTime);
        }

        // do some rendering
        for (viewIt = this->viewports.begin(); viewIt != this->viewports.end(); viewIt++) {
            (*viewIt)->render(this->renderer);
        }
    }

    // how we look into the world, location in the window + width and height
    Viewport *Window::newViewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        Viewport *viewport = new Viewport(x, y, w, h);
        this->viewports.insert(viewport);
        return viewport;
    }

    // containers
    Scene *Window::newScene() {
        Scene *scene = new Scene();
        this->scenes.insert(scene);
        return scene;
    }

    Overlay *Window::newOverlay() {
        Overlay *overlay = new Overlay();
        this->overlays.insert(overlay);
        return overlay;
    }

    bool Window::loadRenderable(Renderable *renderable) {
        return renderable->load(this->renderer); // load'er up -> track loading on renderable
    }

    bool Window::unloadRenderable(Renderable *renderable) {
        return renderable->unload(this->renderer);
    }

    bool Window::loadOverlayRenderable(OverlayRenderable *overRend) {
        return overRend->load(this->renderer);
    }

    bool Window::unloadOverlayRenderable(OverlayRenderable *overRend) {
        return overRend->unload(this->renderer);
    }
}}
