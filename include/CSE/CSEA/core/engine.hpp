#ifndef CSEA_CORE_ENGINE_HPP
#define CSEA_CORE_ENGINE_HPP

#include <set>

#include <CSE/CSEA/render/renderer.hpp>

#include <CSE/CSEA/core/stage.hpp>


namespace CSEA { namespace Core {
    class Engine {
    public:
        struct Settings {
            CSEA::Render::Renderer::WindowSettings windowSettings;
            // other settings later i guess...
        };
    private:
        static CSEA::Core::Stage *previousStage, *activeStage;
        static std::set<CSEA::Core::Stage*> loadedStages;

        static bool isInitialized;

        static bool initializeModules(Settings &settings);
        static void updateModules();
        static void shutdownModules();

        Engine();
        ~Engine();
    public:
        static bool initialize(Settings &settings);
        static void shutdown();

        // loads a stage into the system, must be called first before setting the stage as active
        static bool loadStage(CSEA::Core::Stage *stage);

        // unloades the stage. This should be managed by whoever's using the engine
        // the engine will start complaining if it's shutdown with loaded stages remaining
        static void unloadStage(CSEA::Core::Stage *stage);

        // denies a stage to be active it hasn't been loaded
        static bool setActiveStage(CSEA::Core::Stage *stage);

        static void run(); // runs main loop until engine receives exit command
        static void exit();
    };
}}
#endif
