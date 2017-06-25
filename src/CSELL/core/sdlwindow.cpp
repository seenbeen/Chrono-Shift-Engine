#include <cstdint>
#include <string>
#include <map>

#include <lib/glad/glad.h>

#include <SDL2/SDL.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/sdlwindow.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>

namespace CSELL { namespace Core {
    std::map<unsigned int, SDLWindow *> SDLWindow::windowMap;

    static std::map<unsigned int, InputCallbackHandler::KeyboardKey> keymap;

    static std::map<uint8_t, InputCallbackHandler::MouseButton> mousebuttonmap;

    static struct InitMaps {
        InitMaps() {
            mousebuttonmap[SDL_BUTTON_LEFT] = InputCallbackHandler::MOUSE_LEFT;
            mousebuttonmap[SDL_BUTTON_MIDDLE] = InputCallbackHandler::MOUSE_MIDDLE;
            mousebuttonmap[SDL_BUTTON_RIGHT] = InputCallbackHandler::MOUSE_RIGHT;

            keymap[SDLK_0] = InputCallbackHandler::K_0;
            keymap[SDLK_1] = InputCallbackHandler::K_1;
            keymap[SDLK_2] = InputCallbackHandler::K_2;
            keymap[SDLK_3] = InputCallbackHandler::K_3;
            keymap[SDLK_4] = InputCallbackHandler::K_4;
            keymap[SDLK_5] = InputCallbackHandler::K_5;
            keymap[SDLK_6] = InputCallbackHandler::K_6;
            keymap[SDLK_7] = InputCallbackHandler::K_7;
            keymap[SDLK_8] = CSELL::Core::InputCallbackHandler::K_8;
            keymap[SDLK_9] = CSELL::Core::InputCallbackHandler::K_9;
            keymap[SDLK_a] = CSELL::Core::InputCallbackHandler::K_A;
            keymap[SDLK_b] = CSELL::Core::InputCallbackHandler::K_B;
            keymap[SDLK_c] = CSELL::Core::InputCallbackHandler::K_C;
            keymap[SDLK_d] = CSELL::Core::InputCallbackHandler::K_D;
            keymap[SDLK_e] = CSELL::Core::InputCallbackHandler::K_E;
            keymap[SDLK_f] = CSELL::Core::InputCallbackHandler::K_F;
            keymap[SDLK_g] = CSELL::Core::InputCallbackHandler::K_G;
            keymap[SDLK_h] = CSELL::Core::InputCallbackHandler::K_H;
            keymap[SDLK_i] = CSELL::Core::InputCallbackHandler::K_I;
            keymap[SDLK_j] = CSELL::Core::InputCallbackHandler::K_J;
            keymap[SDLK_k] = CSELL::Core::InputCallbackHandler::K_K;
            keymap[SDLK_l] = CSELL::Core::InputCallbackHandler::K_L;
            keymap[SDLK_m] = CSELL::Core::InputCallbackHandler::K_M;
            keymap[SDLK_n] = CSELL::Core::InputCallbackHandler::K_N;
            keymap[SDLK_o] = CSELL::Core::InputCallbackHandler::K_O;
            keymap[SDLK_p] = CSELL::Core::InputCallbackHandler::K_P;
            keymap[SDLK_q] = CSELL::Core::InputCallbackHandler::K_Q;
            keymap[SDLK_r] = CSELL::Core::InputCallbackHandler::K_R;
            keymap[SDLK_s] = CSELL::Core::InputCallbackHandler::K_S;
            keymap[SDLK_t] = CSELL::Core::InputCallbackHandler::K_T;
            keymap[SDLK_u] = CSELL::Core::InputCallbackHandler::K_U;
            keymap[SDLK_v] = CSELL::Core::InputCallbackHandler::K_V;
            keymap[SDLK_w] = CSELL::Core::InputCallbackHandler::K_W;
            keymap[SDLK_x] = CSELL::Core::InputCallbackHandler::K_X;
            keymap[SDLK_y] = CSELL::Core::InputCallbackHandler::K_Y;
            keymap[SDLK_z] = CSELL::Core::InputCallbackHandler::K_Z;
            keymap[SDLK_SPACE] = CSELL::Core::InputCallbackHandler::K_SPACE;
            keymap[SDLK_EQUALS] = CSELL::Core::InputCallbackHandler::K_EQUAL;
            keymap[SDLK_QUOTE] = CSELL::Core::InputCallbackHandler::K_APOSTROPHE;
            keymap[SDLK_PERIOD] = CSELL::Core::InputCallbackHandler::K_PERIOD;
            keymap[SDLK_COMMA] = CSELL::Core::InputCallbackHandler::K_COMMA;
            keymap[SDLK_MINUS] = CSELL::Core::InputCallbackHandler::K_MINUS;
            keymap[SDLK_SLASH] = CSELL::Core::InputCallbackHandler::K_SLASH;
            keymap[SDLK_BACKSLASH] = CSELL::Core::InputCallbackHandler::K_BACKSLASH;
            keymap[SDLK_SEMICOLON] = CSELL::Core::InputCallbackHandler::K_SEMICOLON;
            keymap[SDLK_LEFTBRACKET] = CSELL::Core::InputCallbackHandler::K_LBRACK;
            keymap[SDLK_RIGHTBRACKET] = CSELL::Core::InputCallbackHandler::K_RBRACK;

            keymap[SDLK_BACKQUOTE] = CSELL::Core::InputCallbackHandler::K_BACKTICK;

            keymap[SDLK_LCTRL] = CSELL::Core::InputCallbackHandler::K_LCTRL;
            keymap[SDLK_RCTRL] = CSELL::Core::InputCallbackHandler::K_RCTRL;
            keymap[SDLK_LALT] = CSELL::Core::InputCallbackHandler::K_LALT;
            keymap[SDLK_RALT] = CSELL::Core::InputCallbackHandler::K_RALT;
            keymap[SDLK_LSHIFT] = CSELL::Core::InputCallbackHandler::K_LSHIFT;
            keymap[SDLK_RSHIFT] = CSELL::Core::InputCallbackHandler::K_RSHIFT;

            keymap[SDLK_UP] = CSELL::Core::InputCallbackHandler::K_UP;
            keymap[SDLK_DOWN] = CSELL::Core::InputCallbackHandler::K_DOWN;
            keymap[SDLK_LEFT] = CSELL::Core::InputCallbackHandler::K_LEFT;
            keymap[SDLK_RIGHT] = CSELL::Core::InputCallbackHandler::K_RIGHT;

            keymap[SDLK_ESCAPE] = CSELL::Core::InputCallbackHandler::K_ESCAPE;
            keymap[SDLK_RETURN] = CSELL::Core::InputCallbackHandler::K_ENTER;
            keymap[SDLK_TAB] = CSELL::Core::InputCallbackHandler::K_TAB;
            keymap[SDLK_BACKSPACE] = CSELL::Core::InputCallbackHandler::K_BACKSPACE;
            keymap[SDLK_INSERT] = CSELL::Core::InputCallbackHandler::K_INSERT;
            keymap[SDLK_DELETE] = CSELL::Core::InputCallbackHandler::K_DELETE;
            keymap[SDLK_HOME] = CSELL::Core::InputCallbackHandler::K_HOME;
            keymap[SDLK_END] = CSELL::Core::InputCallbackHandler::K_END;
            keymap[SDLK_PAGEUP] = CSELL::Core::InputCallbackHandler::K_PAGEUP;
            keymap[SDLK_PAGEDOWN] = CSELL::Core::InputCallbackHandler::K_PAGEDOWN;

            keymap[SDLK_CAPSLOCK] = CSELL::Core::InputCallbackHandler::K_CAPSLOCK;
            keymap[SDLK_SCROLLLOCK] = CSELL::Core::InputCallbackHandler::K_SCROLLLOCK;
            keymap[SDLK_NUMLOCKCLEAR] = CSELL::Core::InputCallbackHandler::K_NUMLOCK;

            keymap[SDLK_PRINTSCREEN] = CSELL::Core::InputCallbackHandler::K_PRINTSCREEN;
            keymap[SDLK_PAUSE] = CSELL::Core::InputCallbackHandler::K_PAUSE;

            keymap[SDLK_F1] = CSELL::Core::InputCallbackHandler::K_F1;
            keymap[SDLK_F2] = CSELL::Core::InputCallbackHandler::K_F2;
            keymap[SDLK_F3] = CSELL::Core::InputCallbackHandler::K_F3;
            keymap[SDLK_F4] = CSELL::Core::InputCallbackHandler::K_F4;
            keymap[SDLK_F5] = CSELL::Core::InputCallbackHandler::K_F5;
            keymap[SDLK_F6] = CSELL::Core::InputCallbackHandler::K_F6;
            keymap[SDLK_F7] = CSELL::Core::InputCallbackHandler::K_F7;
            keymap[SDLK_F8] = CSELL::Core::InputCallbackHandler::K_F8;
            keymap[SDLK_F9] = CSELL::Core::InputCallbackHandler::K_F9;
            keymap[SDLK_F10] = CSELL::Core::InputCallbackHandler::K_F10;
            keymap[SDLK_F11] = CSELL::Core::InputCallbackHandler::K_F11;
            keymap[SDLK_F12] = CSELL::Core::InputCallbackHandler::K_F12;

            keymap[SDLK_KP_0] = CSELL::Core::InputCallbackHandler::K_KEYPAD_0;
            keymap[SDLK_KP_1] = CSELL::Core::InputCallbackHandler::K_KEYPAD_1;
            keymap[SDLK_KP_2] = CSELL::Core::InputCallbackHandler::K_KEYPAD_2;
            keymap[SDLK_KP_3] = CSELL::Core::InputCallbackHandler::K_KEYPAD_3;
            keymap[SDLK_KP_4] = CSELL::Core::InputCallbackHandler::K_KEYPAD_4;
            keymap[SDLK_KP_5] = CSELL::Core::InputCallbackHandler::K_KEYPAD_5;
            keymap[SDLK_KP_6] = CSELL::Core::InputCallbackHandler::K_KEYPAD_6;
            keymap[SDLK_KP_7] = CSELL::Core::InputCallbackHandler::K_KEYPAD_7;
            keymap[SDLK_KP_8] = CSELL::Core::InputCallbackHandler::K_KEYPAD_8;
            keymap[SDLK_KP_9] = CSELL::Core::InputCallbackHandler::K_KEYPAD_9;

            keymap[SDLK_KP_DIVIDE] = CSELL::Core::InputCallbackHandler::K_KEYPAD_DIVIDE;
            keymap[SDLK_KP_MULTIPLY] = CSELL::Core::InputCallbackHandler::K_KEYBOARD_MULTIPLY;
            keymap[SDLK_KP_PLUS] = CSELL::Core::InputCallbackHandler::K_KEYPAD_ADD;
            keymap[SDLK_KP_MINUS] = CSELL::Core::InputCallbackHandler::K_KEYPAD_SUBTRACT;

            keymap[SDLK_KP_DECIMAL] = CSELL::Core::InputCallbackHandler::K_KEYPAD_DECIMAL;
            keymap[SDLK_KP_ENTER] = CSELL::Core::InputCallbackHandler::K_KEYPAD_ENTER;
            keymap[SDLK_KP_EQUALS] = CSELL::Core::InputCallbackHandler::K_KEYPAD_EQUAL;
        }
    } initMaps;

    bool SDLWindow::initializeImplementation(Window::Settings settings) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        this->windowWidth = settings.width;
        this->windowHeight = settings.height;
        this->windowTitle = settings.title;

        unsigned int resizeableFlag = settings.resizeable*SDL_WINDOW_RESIZABLE;

        // Set up Window
        this->window = SDL_CreateWindow(this->windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL | resizeableFlag);

        if (this->window == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - SDLWindow", "SDL Unable to create window!");
            return false;
        }

        this->windowId = SDL_GetWindowID(this->window);
        SDLWindow::windowMap[this->windowId] = this;

        // make ze context
        this->context = SDL_GL_CreateContext(this->window);

        // Set up glad loader to load in gl procs
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - SDLWindow", "Failed to initialize GLAD!");
            return false;
        }

        SDL_GL_SetSwapInterval(1);
        return true;
    }

    void SDLWindow::destroyImplementation() {
        SDLWindow::windowMap.erase(SDLWindow::windowMap.find(this->windowId));
        SDL_GL_DeleteContext(this->context);
        SDL_DestroyWindow(this->window);
    }

    bool SDLWindow::updateImplementation() {
        SDL_GL_SwapWindow(this->window);

        // poll events
        SDL_Event event;
        std::map<unsigned int, SDLWindow *>::iterator it;
        std::map<unsigned int, InputCallbackHandler::KeyboardKey>::iterator keyit;
        std::map<uint8_t, InputCallbackHandler::MouseButton>::iterator buttonit;
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                this->handleWindowCloseInput();
            } else if (event.type == SDL_WINDOWEVENT) {
                it = SDLWindow::windowMap.find(event.window.windowID);
                if (event.window.event == SDL_WINDOWEVENT_ENTER) {
                    it->second->handleMouseEnterLeaveInput(true);
                } else if (event.window.event == SDL_WINDOWEVENT_LEAVE) {
                    it->second->handleMouseEnterLeaveInput(false);
                } else if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    it->second->handleWindowCloseInput();
                } else if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                           event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    it->second->handleWindowResizeInput(event.window.data1, event.window.data2);
                }
            } else if (event.type == SDL_KEYDOWN) {
                keyit = keymap.find(event.key.keysym.sym);
                InputCallbackHandler::KeyboardKey k = keyit == keymap.end() ? InputCallbackHandler::K_UNKNOWN : keyit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); it++) {
                    it->second->handleKeyInput(k, InputCallbackHandler::ACTION_PRESS);
                }
            } else if (event.type == SDL_KEYUP) {
                keyit = keymap.find(event.key.keysym.sym);
                InputCallbackHandler::KeyboardKey k = keyit == keymap.end() ? InputCallbackHandler::K_UNKNOWN : keyit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); it++) {
                    it->second->handleKeyInput(k, InputCallbackHandler::ACTION_RELEASE);
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                buttonit = mousebuttonmap.find(event.button.button);
                InputCallbackHandler::MouseButton mb = buttonit == mousebuttonmap.end() ? InputCallbackHandler::MOUSE_UNKNOWN : buttonit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); it++) {
                    it->second->handleMouseButtonInput(mb, InputCallbackHandler::ACTION_PRESS);
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                buttonit = mousebuttonmap.find(event.button.button);
                InputCallbackHandler::MouseButton mb = buttonit == mousebuttonmap.end() ? InputCallbackHandler::MOUSE_UNKNOWN : buttonit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); it++) {
                    it->second->handleMouseButtonInput(mb, InputCallbackHandler::ACTION_RELEASE);
                }
            } else if (event.type == SDL_MOUSEWHEEL) {
                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); it++) {
                    it->second->handleMouseScrollInput(event.wheel.x, event.wheel.y);
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); it++) {
                    it->second->handleMousePosInput(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                }
            }
		}
		return true;
    }

    double SDLWindow::getTimeImplementation() {
        return SDL_GetTicks()/1000.0;
    }

    bool SDLWindow::useContextImplementation() {
        SDL_GL_MakeCurrent(this->window, this->context);
        return true;
    }

    bool SDLWindow::setCursorModeImplementation(bool enable) {
        int success = 0;
        if (!enable) {
            success = SDL_SetRelativeMouseMode(SDL_TRUE);
        } else {
            success = SDL_SetRelativeMouseMode(SDL_FALSE);
        }

        if (success == 0) {
            return true;
        } else {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Core - SDLWindow", std::string(SDL_GetError()));
            return false;
        }
    }
}}
