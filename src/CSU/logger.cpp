#include <CSE/CSU/logger.hpp>

#include <iostream>
#include <string>

namespace CSU {
    void Logger::log(Logger::LogLevel lv, Logger::EngineLevel elv, const std::string &source, const std::string &message) {
        std::cout << "[" << source << "] " << message << std::endl;
    }
}
