#ifndef CSEA_INPUT_INPUTMANAGER_HPP
#define CSEA_INPUT_INPUTMANAGER_HPP
#include <set>

#include <CSE/CSELL/core/inputcallbackhandler.hpp>
#include <CSE/CSELL/core/inputenum.hpp>

#include <CSE/CSEA/input/inputlistener.hpp>

/*
    Note that this class has no knowledge of any context of what's calling it.
    This allows you to register for multiple windows and create some funky cases if
    you realllllly want to.

    Done this way to prevent heavy coupling of this class to any specific event-producing class.
*/

namespace CSEA { namespace Core {
    class Engine; // forward decls
}}

namespace CSEA { namespace Input {
    class InputManager : public CSELL::Core::InputCallbackHandler {
    friend class CSEA::Core::Engine;
        static InputManager *instance;

        std::set<InputListener*> listeners;

        InputManager();
        ~InputManager();

        static bool initialize();
        static void shutdown();

        // registry functions
        bool onRegisterInputListener(InputListener *listener);
        // unregistry functions
        bool onUnregisterInputListener(InputListener *listener);

    public:
        static bool registerInputListener(InputListener *listener);
        static bool unregisterInputListener(InputListener *listener);

        // own dispatchers
        void handleKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action);
        void handleMousePosInput(double xpos, double ypos, double xrel, double yrel);
        void handleMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action);
        void handleMouseScrollInput(double xoffset, double yoffset);
        void handleMouseEnterLeaveInput(bool entered);
        void handleWindowResizeInput(unsigned int width, unsigned int height);
        void handleWindowCloseInput();
    };
}}
#endif
