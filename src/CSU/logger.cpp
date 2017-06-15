#include <CSE/CSU/logger.hpp>

#include <iostream>

namespace CSU {
    void Logger::log(Logger::LogLevel lv, Logger::EngineLevel elv, const char *source, const char *message) {
        std::cout << "[" << source << "] " << message << std::endl;
    }
}
