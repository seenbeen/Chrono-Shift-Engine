#ifndef CSELL_CORE_TIME_HPP
#define CSELL_CORE_TIME_HPP

namespace CSELL { namespace Core {
    class Time {
        static bool isInitialized;
    public:
        static bool initialize();
        static bool shutdown();
        static double getTime();
    };
}}

#endif
