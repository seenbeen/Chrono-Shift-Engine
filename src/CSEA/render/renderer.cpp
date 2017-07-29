#include <CSE/CSELL/render/gl/glrendererimple.hpp>

#include <CSE/CSELL/core/sdlwindow.hpp>

#include <CSE/CSEA/core/time.hpp>
#include <CSE/CSEA/render/renderer.hpp>

#include <CSE/CSU/logger.hpp>

namespace CSEA { namespace Render {
    bool Renderer::isInitialized = false;
    Window* Renderer::window;
    CSELL::Render::RendererImple *Renderer::rimple;

    Renderer::Renderer() {}
    Renderer::~Renderer() {}

    bool Renderer::initialize() {
        if (Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer already initialized!");
            return false;
        }

        Renderer::isInitialized = CSELL::Core::SDLWindow::initialize();
        if (Renderer::isInitialized) {
            Renderer::rimple = new CSELL::Render::GLRendererImple();
            return true;
        }
        return false;
    }

    void Renderer::update() {
        Renderer::window->update(CSEA::Core::Time::getDeltaTime());
    }

    void Renderer::shutdown() {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Trying to shutdown uninitialized Renderer!");
            return;
        }

        CSELL::Core::SDLWindow::shutdown();

        Renderer::isInitialized = false;
    }

    Window *Renderer::initWindow(Window::Settings &settings) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not initialized!");
            return NULL;
        }
        if (Renderer::window != NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Render - Renderer",
                             "Unable to init Window - Window has already been initialized!");
            return NULL;
        }

        Window *window = new Window(new CSELL::Core::SDLWindow(), Renderer::rimple, settings);
        if (window->successfulInit) {
            Renderer::window = window;
            return window;
        }
        delete window;

        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                         "Render - Renderer", "Failed to properly initialize window in newWindow.");

        return NULL;
    }

    void Renderer::deleteWindow() {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not initialized!");
            return;
        }

        if (Renderer::window == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Unable to delete Window - Window not initialized!");
            return;
        }

        delete Renderer::window;
        Renderer::window = NULL;
    }
}}
