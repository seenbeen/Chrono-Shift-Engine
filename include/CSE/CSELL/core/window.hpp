#ifndef CSELL_CORE_WINDOW_HPP
#define CSELL_CORE_WINDOW_HPP

#include <string>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/inputcallbackhandler.hpp>

namespace CSELL { namespace Core {
    class Window {
    public:
        struct Settings {
            unsigned int width;
            unsigned int height;
            std::string title;
            bool resizeable;
        };

    private:
        InputCallbackHandler *callbackHandler;
        bool successfulInit;

    protected:
        virtual ~Window();
        virtual bool initializeImplementation(Window::Settings settings) = 0;
        virtual void destroyImplementation() = 0;
        virtual void updateImplementation() = 0;
        virtual double getTimeImplementation() = 0;
        virtual void useContextImplementation() = 0;

    public:
        bool initialize(Window::Settings settings);
        void destroy();

        void registerInputCallbackHandler(InputCallbackHandler *cbh);

        void handleKeyInput(int key, int action, int mods);
        void handleMousePosInput(double xpos, double ypos);
        void handleMouseButtonInput(int button, int action, int mods);
        void handleMouseScrollInput(double xoffset, double yoffset);
        void handleMouseEnterLeaveInput(int entered);

        void update();
        double getTime();
        void useContext();
    };
}}

#endif
