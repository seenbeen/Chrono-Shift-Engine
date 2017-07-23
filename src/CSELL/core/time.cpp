#include <lib/SDL2/SDL.h>

#include <CSE/CSELL/core/time.hpp>
#include <CSE/CSU/logger.hpp>

namespace CSELL { namespace Core {
    bool Time::isInitialized = false;

    bool Time::initialize() {
        if (Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - Time", "Time is already initialized!");
            return false;
        }
        int success = SDL_InitSubSystem(SDL_INIT_TIMER);
        if (success != 0) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - Time", SDL_GetError());
            return false;
        }
        Time::isInitialized = true;
        return true;
    }

    bool Time::shutdown() {
        if (!Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - Time", "Time is not initialized!");
            return false;
        }
        SDL_QuitSubSystem(SDL_INIT_TIMER);
        Time::isInitialized = false;
        return true;
    }

    double Time::getTime() {
        if (!Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - Time", "Time is not initialized!");
            return -1.0;
        }
        return SDL_GetTicks()/1000.0;
    }
}}
