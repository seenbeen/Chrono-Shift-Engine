#ifndef CSELL_CORE_INPUTCALLBACKHANDLER_HPP
#define CSELL_CORE_INPUTCALLBACKHANDLER_HPP

#include <CSE/CSELL/Core/inputenum.hpp>

namespace CSELL { namespace Core {
    class InputCallbackHandler {
        friend class Window;
        protected:
            virtual void handleKeyInput(InputEnum::KeyboardKey key, InputEnum::InputAction action) = 0;
            virtual void handleMousePosInput(double xpos, double ypos, double xrel, double yrel) = 0;
            virtual void handleMouseButtonInput(InputEnum::MouseButton button, InputEnum::InputAction action) = 0;
            virtual void handleMouseScrollInput(double xoffset, double yoffset) = 0;
            virtual void handleMouseEnterLeaveInput(bool entered) = 0;

            virtual void handleWindowResizeInput(unsigned int width, unsigned int height) = 0;
            virtual void handleWindowCloseInput() = 0;
    };
}}

#endif
