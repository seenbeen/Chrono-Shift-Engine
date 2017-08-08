#ifndef CSEA_INPUT_INPUTLISTENER_HPP
#define CSEA_INPUT_INPUTLISTENER_HPP

#include <CSE/CSELL/core/inputcallbackhandler.hpp>

namespace CSEA { namespace Input {
    class InputListener {
    friend class InputManager;
        bool isEnabled;
    protected:
        virtual void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action);
        virtual void onMousePosInput(double xpos, double ypos, double xrel, double yrel);
        virtual void onMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action);
        virtual void onMouseScrollInput(double xoffset, double yoffset);
        virtual void onMouseEnterLeaveInput(bool entered);

        virtual void onWindowResizeInput(unsigned int width, unsigned int height);
        virtual void onWindowCloseInput();
        InputListener();
    public:
        void setListenerIsEnabled(bool isEnabled);
    };
}}
#endif
