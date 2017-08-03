#include <CSE/CSELL/core/time.hpp>
#include <CSE/CSEA/core/time.hpp>

#include <CSE/CSU/logger.hpp>

namespace CSEA { namespace Core {
    bool Time::isInitialized = false;
    double Time::elapsedTime = 0.0;
    double Time::deltaTime = 0.0;

    Time::Time() {}
    Time::~Time() {}

    bool Time::initialize() {
        if (Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Core - Time", "Time is already Initialized!");
            return false;
        }
        Time::isInitialized = CSELL::Core::Time::initialize();
        return Time::isInitialized;
    }

    void Time::update() {
        double currentTime = CSELL::Core::Time::getTime();
        Time::deltaTime = currentTime - Time::elapsedTime;
        Time::elapsedTime = currentTime;
    }

    void Time::shutdown() {
        if (!Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Core - Time", "Trying to shutdown uninitialized Time!");
            return;
        }

        CSELL::Core::Time::shutdown();

        Time::isInitialized = false;
    }

    double Time::getDeltaTime() {
        if (!Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Core - Time", "Time is not initialized!");
            return -1.0;
        }

        return Time::deltaTime;
    }

    double Time::getElapsedTime() {
        if (!Time::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA,
                             "Core - Time", "Time is not initialized!");
            return -1.0;
        }

        return Time::elapsedTime;
    }
}}
