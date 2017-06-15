#include <CSE/CSU/logger.hpp>

#include <iostream>
#include <string>

namespace CSU {
    void Logger::log(Logger::LogLevel lv, Logger::EngineLevel elv, std::string const &source, std::string const &message) {
        std::cout << "[" << source << "] " << message << std::endl;
    }
}
