#ifndef CSEA_CORE_TIME_HPP
#define CSEA_CORE_TIME_HPP

namespace CSEA { namespace Core {
    class Engine;
}}

namespace CSEA { namespace Core {
    class Time {
    friend class Engine;
        static bool isInitialized;
        static double elapsedTime;
        static double deltaTime;

        Time();
        ~Time();

        static bool initialize();
        static void update();
        static void shutdown();
    public:
        static double getDeltaTime();
        static double getElapsedTime();
    };
}}

#endif
