#ifndef CSU_LOGGER_HPP
#define CSU_LOGGER_HPP

namespace CSU {
    class Logger {
        // should proly save these logs somewhere
        // might wanna initialize this system as well
        //  for example to save the time + date / filename
    public:
        enum LogLevel { FATAL, WARN, DEBUG, INFO, OFF };
        enum EngineLevel { CSELL, CSEA, CSEF };

        static void log(Logger::LogLevel lv, Logger::EngineLevel elv, const char *source, const char *message);
    };
}


#endif