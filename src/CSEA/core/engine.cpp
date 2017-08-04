#include <set>

#include <lib/SDL2/SDL.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/core/engine.hpp>
#include <CSE/CSEA/core/time.hpp>
#include <CSE/CSEA/asset/assetmanager.hpp>
#include <CSE/CSEA/render/renderer.hpp>
#include <CSE/CSEA/input/inputmanager.hpp>

/*
Notes:
- in the release version, all this "loaded stage checking" isn't required and should be removed,
    under the assumption that the debug version runs without complaints
*/

namespace CSEA { namespace Core {
    Engine::Engine() {}
    Engine::~Engine() {}

    bool Engine::isInitialized = false;

    std::set<CSEA::Core::Stage*> Engine::loadedStages;
    CSEA::Core::Stage *Engine::previousStage = NULL, *Engine::activeStage = NULL;

    bool Engine::initializeModules(Settings &settings) {
        if (!CSEA::Core::Time::initialize()) {
            return false;
        }
        if (!CSEA::Assets::AssetManager::initialize()) {
            CSEA::Core::Time::shutdown();
            return false;
        }
        if (!CSEA::Render::Renderer::initialize(settings.windowSettings)) {
            CSEA::Assets::AssetManager::shutdown();
            CSEA::Core::Time::shutdown();
            return false;
        }
        if (!CSEA::Input::InputManager::initialize()) {
            CSEA::Render::Renderer::shutdown();
            CSEA::Assets::AssetManager::shutdown();
            CSEA::Core::Time::shutdown();
            return false;
        }
        CSEA::Render::Renderer::registerInputCallbackHandler(CSEA::Input::InputManager::instance);
        return true;
    }

    void Engine::shutdownModules() {
        CSEA::Input::InputManager::shutdown();
        CSEA::Render::Renderer::shutdown();
        CSEA::Assets::AssetManager::shutdown();
        CSEA::Core::Time::shutdown();
        SDL_Quit();
    }

    void Engine::updateModules() {
        CSEA::Core::Time::update();
        CSEA::Render::Renderer::update(CSEA::Core::Time::getDeltaTime());
    }

    bool Engine::initialize(Settings &settings) {
        if (Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Core - Engine",
                             "Engine already initialized!");
            return false;
        }
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Core - Engine", "Initializing.");

        Engine::isInitialized = Engine::initializeModules(settings);

        if (Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Core - Engine", "Successful Initialization.");
            return true;
        }
        return false;
    }

    void Engine::shutdown() {
        if (!Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Core - Engine",
                             "Cannot shutdown uninitialized Engine!");
            return;
        }
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Core - Engine", "Shutting Down.");
        // unload all loaded stages
        std::set<CSEA::Core::Stage*>::iterator it;
        for (it = Engine::loadedStages.begin(); it != Engine::loadedStages.end(); ++it) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine",
                            "Not all Stages unloaded prior to engine shutdown!");
            (*it)->onUnload();
        }

        Engine::shutdownModules();

        Engine::isInitialized = false;
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Core - Engine", "Successful Shut Down.");
    }

    bool Engine::loadStage(CSEA::Core::Stage *stage) {
        if (!Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Core - Engine", "Engine is not Initialized!");
            return false;
        } else if (stage == NULL) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine", "Unable to load NULL stage!");
            return false;
        }

        std::set<CSEA::Core::Stage*>::iterator it = Engine::loadedStages.find(stage);

        if (it != Engine::loadedStages.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine", "Trying to load Loaded Stage!");
            return false;
        }

        Engine::loadedStages.insert(stage);

        stage->load(); // load'er up

        return true;
    }

    void Engine::unloadStage(CSEA::Core::Stage *stage) {
        if (!Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Core - Engine", "Engine is not Initialized!");
            return;
        } else if (stage == NULL) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine", "Unable to unload NULL stage!");
            return;
        }

        std::set<CSEA::Core::Stage*>::iterator it = Engine::loadedStages.find(stage);

        if (it == Engine::loadedStages.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine", "Trying to unload non-loaded Stage!");
            return;
        }

        Engine::loadedStages.erase(it);

        stage->unload();
    }

    bool Engine::setActiveStage(CSEA::Core::Stage *stage) {
        if (!Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Core - Engine", "Engine is not Initialized!");
            return false;
        } else if (stage == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Core - Engine", "Unable to set active Stage to NULL!");
            return false;
        }

        std::set<CSEA::Core::Stage*>::iterator it = Engine::loadedStages.find(stage);

        if (it == Engine::loadedStages.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine", "Trying to set non-loaded Stage active!");
            return false;
        }

        Engine::activeStage = stage;
        return true;
    }

    void Engine::exit() {
        if (Engine::activeStage != NULL) {
            CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Core - Engine", "Exit.");
            Engine::activeStage->transitionOutOf();
            Engine::activeStage = NULL;
            Engine::previousStage = NULL;
            return;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Core - Engine", "Attempting to exit non-running Engine.");
    }

    void Engine::run() {
        if (!Engine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Core - Engine", "Engine is not Initialized!");
            return;
        } else if (Engine::activeStage == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Core - Engine", "Trying to start engine with no active Stage!");
            return;
        }

        while (Engine::activeStage != NULL) {
            if (Engine::previousStage != Engine::activeStage) {
                if (Engine::previousStage != NULL) {
                    Engine::previousStage->transitionOutOf();
                }
                Engine::previousStage = Engine::activeStage;
                Engine::activeStage->transitionInto();
            }
            Engine::updateModules();
            if (Engine::activeStage != NULL) {
                Engine::activeStage->update(CSEA::Core::Time::getDeltaTime());
            }
        }
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Core - Engine", "Exited.");
    }
}}
