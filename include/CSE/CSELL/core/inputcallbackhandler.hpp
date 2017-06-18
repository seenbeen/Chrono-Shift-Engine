#ifndef CSELL_CORE_INPUTCALLBACKHANDLER_HPP
#define CSELL_CORE_INPUTCALLBACKHANDLER_HPP

namespace CSELL { namespace Core {
    class InputCallbackHandler {
        friend class Window;
        public:
            enum KeyboardKey {
                K_UNKNOWN,

                K_0, K_1, K_2, K_3, K_4,
                K_5, K_6, K_7, K_8, K_9,

                K_A, K_B, K_C, K_D, K_E,
                K_F, K_G, K_H, K_I, K_J,
                K_K, K_L, K_M, K_N, K_O,
                K_P, K_Q, K_R, K_S, K_T,
                K_U, K_V, K_W, K_X, K_Y,
                K_Z,

                K_SPACE, K_EQUAL,

                K_APOSTROPHE, K_PERIOD, K_COMMA,
                K_MINUS, K_SLASH, K_BACKSLASH,
                K_SEMICOLON, K_LBRACK, K_RBRACK,

                K_BACKTICK,

                K_LCTRL, K_RCTRL,
                K_LALT, K_RALT,
                K_LSHIFT, K_RSHIFT,

                K_UP, K_DOWN, K_LEFT, K_RIGHT,

                K_ESCAPE, K_ENTER, K_TAB, K_BACKSPACE,
                K_INSERT, K_DELETE,
                K_HOME, K_END, K_PAGEUP, K_PAGEDOWN,

                K_CAPSLOCK, K_SCROLLLOCK, K_NUMLOCK,

                K_PRINTSCREEN, K_PAUSE,

                K_F1, K_F2, K_F3, K_F4, K_F5, K_F6,
                K_F7, K_F8, K_F9, K_F10, K_F11, K_F12,

                K_KEYPAD_0, K_KEYPAD_1, K_KEYPAD_2,
                K_KEYPAD_3, K_KEYPAD_4, K_KEYPAD_5,
                K_KEYPAD_6, K_KEYPAD_7, K_KEYPAD_8,
                K_KEYPAD_9,

                K_KEYPAD_DIVIDE, K_KEYBOARD_MULTIPLY,
                K_KEYPAD_ADD, K_KEYPAD_SUBTRACT,

                K_KEYPAD_DECIMAL, K_KEYPAD_ENTER, K_KEYPAD_EQUAL
            };

            enum InputAction { ACTION_UNKNOWN, ACTION_PRESS, ACTION_RELEASE };

            enum MouseButton { MOUSE_UNKNOWN, MOUSE_LEFT, MOUSE_MIDDLE, MOUSE_RIGHT };
        protected:
            virtual void handleKeyInput(InputCallbackHandler::KeyboardKey key, InputCallbackHandler::InputAction action) = 0;
            virtual void handleMousePosInput(double xpos, double ypos) = 0;
            virtual void handleMouseButtonInput(InputCallbackHandler::MouseButton button, InputCallbackHandler::InputAction action) = 0;
            virtual void handleMouseScrollInput(double xoffset, double yoffset) = 0;
            virtual void handleMouseEnterLeaveInput(bool entered) = 0;

            virtual void handleWindowResizeInput(unsigned int width, unsigned int height) = 0;
            virtual void handleWindowCloseInput() = 0;
    };
}}

#endif
