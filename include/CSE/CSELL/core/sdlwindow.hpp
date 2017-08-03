#ifndef CSELL_CORE_SDLWINDOW_HPP
#define CSELL_CORE_SDLWINDOW_HPP

#include <string>
#include <map>

#include <lib/SDL2/SDL.h>

#include <CSE/CSELL/core/window.hpp>

namespace CSELL { namespace Core {
    class SDLWindow : public Window {
        static std::map<unsigned int, SDLWindow *> windowMap;
        static bool isInitialized;

        unsigned int windowWidth, windowHeight, windowId;
        std::string windowTitle;
        SDL_Window *window;
        SDL_GLContext context;
    protected:
        bool initializeImplementation(Window::Settings settings);
        void destroyImplementation();
        bool updateImplementation();
        bool useContextImplementation();
        bool setCursorModeImplementation(bool enable);
    public:
        static bool initialize();
        static bool shutdown();
        SDLWindow();
    };
}}
#endif
