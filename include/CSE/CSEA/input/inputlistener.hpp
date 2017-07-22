#ifndef CSEA_INPUT_INPUTLISTENER_HPP
#define CSEA_INPUT_INPUTLISTENER_HPP

#include <CSE/CSELL/core/inputcallbackhandler.hpp>

namespace CSEA { namespace Input {
    class InputListener {
    friend class InputManager;
    protected:
        virtual void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) = 0;
        virtual void onMousePosInput(double xpos, double ypos, double xrel, double yrel) = 0;
        virtual void onMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action) = 0;
        virtual void onMouseScrollInput(double xoffset, double yoffset) = 0;
        virtual void onMouseEnterLeaveInput(bool entered) = 0;

        virtual void onWindowResizeInput(unsigned int width, unsigned int height) = 0;
        virtual void onWindowCloseInput() = 0;
    };
}}
#endif
