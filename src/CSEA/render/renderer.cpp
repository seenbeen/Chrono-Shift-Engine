#include <CSE/CSEA/render/renderer.hpp>

#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/gl/glrendererimple.hpp>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/core/sdlwindow.hpp>

#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/renderable.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>


namespace CSEA { namespace Render {
    bool Renderer::isInitialized = false;

    CSELL::Core::Window *Renderer::window = NULL;
    CSELL::Render::RendererImple *Renderer::rimple = NULL;
    CSELL::Render::Renderer* Renderer::renderer = NULL;
    CacheManager *Renderer::cacheManager = NULL;

    std::set<Scene*> Renderer::scenes;
    std::set<Viewport*> Renderer::viewports;

    Renderer::Renderer() {}
    Renderer::~Renderer() {}

    bool Renderer::initialize(WindowSettings &settings) {
        if (Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer already initialized!");
            return false;
        }

        if (CSELL::Core::SDLWindow::initialize()) {
            CSELL::Core::Window::Settings csellWinSettings;
            csellWinSettings.width = settings.width;
            csellWinSettings.height = settings.height;
            csellWinSettings.title = settings.windowTitle;
            csellWinSettings.resizeable = settings.isResizeable;

            Renderer::window = new CSELL::Core::SDLWindow();

            if (!Renderer::window->initialize(csellWinSettings)) {
                Renderer::window->destroy();
                Renderer::window = NULL;
                return false;
            }

            Renderer::window->useContext();

            Renderer::rimple = new CSELL::Render::GLRendererImple();
            Renderer::renderer = CSELL::Render::Renderer::newRenderer(Renderer::window, Renderer::rimple);

            if (Renderer::renderer != NULL) {
                Renderer::renderer->makeActiveRenderer();
                Renderer::cacheManager = new CacheManager(Renderer::renderer);
                Renderer::isInitialized = true;
                return true;
            }

            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Failed to properly initialize renderer.");

            delete Renderer::rimple;
            Renderer::window->destroy();

            Renderer::rimple = NULL;
            Renderer::window = NULL;

            CSELL::Core::SDLWindow::shutdown();
        }

        return false;
    }

    void Renderer::update(double deltaTime) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return;
        }

        std::set<Scene*>::iterator sceneIt;
        std::set<Viewport*>::iterator viewIt;

        // update active scenes
        for (sceneIt = Renderer::scenes.begin(); sceneIt != Renderer::scenes.end(); ++sceneIt) {
            (*sceneIt)->update(deltaTime);
        }

        // do some rendering
        Renderer::renderer->clearColour(0.0f, 0.0f, 0.0f, 1.0f);
        for (viewIt = Renderer::viewports.begin(); viewIt != Renderer::viewports.end(); ++viewIt) {
            (*viewIt)->render(Renderer::renderer);
        }
        Renderer::window->update();
    }

    void Renderer::shutdown() {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Trying to shutdown uninitialized Renderer!");
            return;
        }

        delete Renderer::cacheManager;
        delete Renderer::renderer;
        delete Renderer::rimple;
        Renderer::window->destroy();

        Renderer::cacheManager = NULL;
        Renderer::renderer = NULL;
        Renderer::rimple = NULL;
        Renderer::window = NULL;

        CSELL::Core::SDLWindow::shutdown();

        Renderer::isInitialized = false;
    }

    bool Renderer::registerInputCallbackHandler(CSELL::Core::InputCallbackHandler *handler) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return NULL;
        }
        return Renderer::window->registerInputCallbackHandler(handler);
    }

    bool Renderer::addViewport(Viewport *viewport) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return NULL;
        }
        if (Renderer::viewports.find(viewport) != Renderer::viewports.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Render - Renderer", "Viewport already added!");
            return false;
        }
        Renderer::viewports.insert(viewport);
        return true;
    }

    bool Renderer::addScene(Scene *scene) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return NULL;
        }
        if (Renderer::scenes.find(scene) != Renderer::scenes.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Render - Renderer", "Scene already added!");
            return false;
        }
        Renderer::scenes.insert(scene);
        scene->onLoad();
        return true;
    }

    bool Renderer::removeViewport(Viewport *viewport) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return NULL;
        }
        if (Renderer::viewports.find(viewport) == Renderer::viewports.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Render - Renderer", "Removing non-existent Viewport!");
            return false;
        }
        Renderer::viewports.erase(Renderer::viewports.find(viewport));
        return true;
    }

    bool Renderer::removeScene(Scene *scene) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return NULL;
        }
        if (Renderer::scenes.find(scene) == Renderer::scenes.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Render - Renderer", "Removing non-existent Scene!");
            return false;
        }
        scene->onUnload();
        Renderer::scenes.erase(Renderer::scenes.find(scene));
        return true;
    }

    bool Renderer::loadRenderable(Renderable *renderable) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return false;
        }
        return renderable->load(Renderer::renderer, Renderer::cacheManager);
    }

    bool Renderer::unloadRenderable(Renderable *renderable) {
        if (!Renderer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Render - Renderer", "Renderer is not Initialized!");
            return false;
        }
        return renderable->unload(Renderer::renderer, Renderer::cacheManager);
    }
}}
