#include <CSE/CSU/logger.hpp>

#include <iostream>
#include <string>

namespace CSU {
    void Logger::log(Logger::LogLevel lv, Logger::EngineLevel elv, const std::string &source, const std::string &message) {
        std::string lvStr, elvStr;
        switch (lv) {
        case Logger::INFO:
            lvStr = "INFO";
            break;
        case Logger::DEBUG:
            lvStr = "DEBUG";
            break;
        case Logger::WARN:
            lvStr = "WARN";
            break;
        case Logger::FATAL:
            lvStr = "FATAL";
            break;
        default:
            lvStr = "UNKNOWN";
        }
        switch (elv) {
        case Logger::CSELL:
            elvStr = "CSELL";
            break;
        case Logger::CSEA:
            elvStr = "CSEA";
            break;
        case Logger::CSEF:
            elvStr = "CSEF";
            break;
        case Logger::EXPERIMENTAL:
            elvStr = "TEST";
            break;
        default:
            elvStr = "UNKNOWN";
        }
        std::cout << "Logger: " << lvStr << " [" << elvStr << " - " << source << "] " << message << std::endl;
    }
}
