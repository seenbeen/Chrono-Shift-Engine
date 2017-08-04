#include <string>
#include <map>

#include <lib/glad/glad.h>

#include <lib/SDL2/SDL.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/sdlwindow.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>
#include <CSE/CSELL/core/inputenum.hpp>

namespace CSELL { namespace Core {
    std::map<unsigned int, SDLWindow *> SDLWindow::windowMap;

    bool SDLWindow::isInitialized = false;

    static std::map<unsigned int, InputEnum::KeyboardKey> keymap;

    static std::map<uint8_t, InputEnum::MouseButton> mousebuttonmap;

    static struct InitMaps {
        InitMaps() {
            mousebuttonmap[SDL_BUTTON_LEFT] = InputEnum::MOUSE_LEFT;
            mousebuttonmap[SDL_BUTTON_MIDDLE] = InputEnum::MOUSE_MIDDLE;
            mousebuttonmap[SDL_BUTTON_RIGHT] = InputEnum::MOUSE_RIGHT;

            keymap[SDLK_0] = InputEnum::K_0;
            keymap[SDLK_1] = InputEnum::K_1;
            keymap[SDLK_2] = InputEnum::K_2;
            keymap[SDLK_3] = InputEnum::K_3;
            keymap[SDLK_4] = InputEnum::K_4;
            keymap[SDLK_5] = InputEnum::K_5;
            keymap[SDLK_6] = InputEnum::K_6;
            keymap[SDLK_7] = InputEnum::K_7;
            keymap[SDLK_8] = InputEnum::K_8;
            keymap[SDLK_9] = InputEnum::K_9;
            keymap[SDLK_a] = InputEnum::K_A;
            keymap[SDLK_b] = InputEnum::K_B;
            keymap[SDLK_c] = InputEnum::K_C;
            keymap[SDLK_d] = InputEnum::K_D;
            keymap[SDLK_e] = InputEnum::K_E;
            keymap[SDLK_f] = InputEnum::K_F;
            keymap[SDLK_g] = InputEnum::K_G;
            keymap[SDLK_h] = InputEnum::K_H;
            keymap[SDLK_i] = InputEnum::K_I;
            keymap[SDLK_j] = InputEnum::K_J;
            keymap[SDLK_k] = InputEnum::K_K;
            keymap[SDLK_l] = InputEnum::K_L;
            keymap[SDLK_m] = InputEnum::K_M;
            keymap[SDLK_n] = InputEnum::K_N;
            keymap[SDLK_o] = InputEnum::K_O;
            keymap[SDLK_p] = InputEnum::K_P;
            keymap[SDLK_q] = InputEnum::K_Q;
            keymap[SDLK_r] = InputEnum::K_R;
            keymap[SDLK_s] = InputEnum::K_S;
            keymap[SDLK_t] = InputEnum::K_T;
            keymap[SDLK_u] = InputEnum::K_U;
            keymap[SDLK_v] = InputEnum::K_V;
            keymap[SDLK_w] = InputEnum::K_W;
            keymap[SDLK_x] = InputEnum::K_X;
            keymap[SDLK_y] = InputEnum::K_Y;
            keymap[SDLK_z] = InputEnum::K_Z;
            keymap[SDLK_SPACE] = InputEnum::K_SPACE;
            keymap[SDLK_EQUALS] = InputEnum::K_EQUAL;
            keymap[SDLK_QUOTE] = InputEnum::K_APOSTROPHE;
            keymap[SDLK_PERIOD] = InputEnum::K_PERIOD;
            keymap[SDLK_COMMA] = InputEnum::K_COMMA;
            keymap[SDLK_MINUS] = InputEnum::K_MINUS;
            keymap[SDLK_SLASH] = InputEnum::K_SLASH;
            keymap[SDLK_BACKSLASH] = InputEnum::K_BACKSLASH;
            keymap[SDLK_SEMICOLON] = InputEnum::K_SEMICOLON;
            keymap[SDLK_LEFTBRACKET] = InputEnum::K_LBRACK;
            keymap[SDLK_RIGHTBRACKET] = InputEnum::K_RBRACK;

            keymap[SDLK_BACKQUOTE] = InputEnum::K_BACKTICK;

            keymap[SDLK_LCTRL] = InputEnum::K_LCTRL;
            keymap[SDLK_RCTRL] = InputEnum::K_RCTRL;
            keymap[SDLK_LALT] = InputEnum::K_LALT;
            keymap[SDLK_RALT] = InputEnum::K_RALT;
            keymap[SDLK_LSHIFT] = InputEnum::K_LSHIFT;
            keymap[SDLK_RSHIFT] = InputEnum::K_RSHIFT;

            keymap[SDLK_UP] = InputEnum::K_UP;
            keymap[SDLK_DOWN] = InputEnum::K_DOWN;
            keymap[SDLK_LEFT] = InputEnum::K_LEFT;
            keymap[SDLK_RIGHT] = InputEnum::K_RIGHT;

            keymap[SDLK_ESCAPE] = InputEnum::K_ESCAPE;
            keymap[SDLK_RETURN] = InputEnum::K_ENTER;
            keymap[SDLK_TAB] = InputEnum::K_TAB;
            keymap[SDLK_BACKSPACE] = InputEnum::K_BACKSPACE;
            keymap[SDLK_INSERT] = InputEnum::K_INSERT;
            keymap[SDLK_DELETE] = InputEnum::K_DELETE;
            keymap[SDLK_HOME] = InputEnum::K_HOME;
            keymap[SDLK_END] = InputEnum::K_END;
            keymap[SDLK_PAGEUP] = InputEnum::K_PAGEUP;
            keymap[SDLK_PAGEDOWN] = InputEnum::K_PAGEDOWN;

            keymap[SDLK_CAPSLOCK] = InputEnum::K_CAPSLOCK;
            keymap[SDLK_SCROLLLOCK] = InputEnum::K_SCROLLLOCK;
            keymap[SDLK_NUMLOCKCLEAR] = InputEnum::K_NUMLOCK;

            keymap[SDLK_PRINTSCREEN] = InputEnum::K_PRINTSCREEN;
            keymap[SDLK_PAUSE] = InputEnum::K_PAUSE;

            keymap[SDLK_F1] = InputEnum::K_F1;
            keymap[SDLK_F2] = InputEnum::K_F2;
            keymap[SDLK_F3] = InputEnum::K_F3;
            keymap[SDLK_F4] = InputEnum::K_F4;
            keymap[SDLK_F5] = InputEnum::K_F5;
            keymap[SDLK_F6] = InputEnum::K_F6;
            keymap[SDLK_F7] = InputEnum::K_F7;
            keymap[SDLK_F8] = InputEnum::K_F8;
            keymap[SDLK_F9] = InputEnum::K_F9;
            keymap[SDLK_F10] = InputEnum::K_F10;
            keymap[SDLK_F11] = InputEnum::K_F11;
            keymap[SDLK_F12] = InputEnum::K_F12;

            keymap[SDLK_KP_0] = InputEnum::K_KEYPAD_0;
            keymap[SDLK_KP_1] = InputEnum::K_KEYPAD_1;
            keymap[SDLK_KP_2] = InputEnum::K_KEYPAD_2;
            keymap[SDLK_KP_3] = InputEnum::K_KEYPAD_3;
            keymap[SDLK_KP_4] = InputEnum::K_KEYPAD_4;
            keymap[SDLK_KP_5] = InputEnum::K_KEYPAD_5;
            keymap[SDLK_KP_6] = InputEnum::K_KEYPAD_6;
            keymap[SDLK_KP_7] = InputEnum::K_KEYPAD_7;
            keymap[SDLK_KP_8] = InputEnum::K_KEYPAD_8;
            keymap[SDLK_KP_9] = InputEnum::K_KEYPAD_9;

            keymap[SDLK_KP_DIVIDE] = InputEnum::K_KEYPAD_DIVIDE;
            keymap[SDLK_KP_MULTIPLY] = InputEnum::K_KEYBOARD_MULTIPLY;
            keymap[SDLK_KP_PLUS] = InputEnum::K_KEYPAD_ADD;
            keymap[SDLK_KP_MINUS] = InputEnum::K_KEYPAD_SUBTRACT;

            keymap[SDLK_KP_DECIMAL] = InputEnum::K_KEYPAD_DECIMAL;
            keymap[SDLK_KP_ENTER] = InputEnum::K_KEYPAD_ENTER;
            keymap[SDLK_KP_EQUALS] = InputEnum::K_KEYPAD_EQUAL;
        }
    } initMaps;

    bool SDLWindow::initialize() {
        if (SDLWindow::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - SDLWindow", "SDLWindow system is already initialized!");
            return false;
        }
        int success = SDL_InitSubSystem(SDL_INIT_VIDEO);
        if (success != 0) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - SDLWindow", SDL_GetError());
            return false;
        }
        SDLWindow::isInitialized = true;
        return true;
    }

    bool SDLWindow::shutdown() {
        if (!SDLWindow::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - SDLWindow", "SDLWindow system is not initialized!");
            return false;
        }
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDLWindow::isInitialized = false;
        return true;
    }

    bool SDLWindow::initializeImplementation(Window::Settings settings) {
        if (!SDLWindow::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Core - SDLWindow", "SDLWindow system is not initialized!");
            return false;
        }
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
        std::map<unsigned int, InputEnum::KeyboardKey>::iterator keyit;
        std::map<uint8_t, InputEnum::MouseButton>::iterator buttonit;
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
                //    it->second->handleWindowCloseInput();
                } else if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                           event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    it->second->handleWindowResizeInput(event.window.data1, event.window.data2);
                }
            } else if (event.type == SDL_KEYDOWN) {
                keyit = keymap.find(event.key.keysym.sym);
                InputEnum::KeyboardKey k = keyit == keymap.end() ? InputEnum::K_UNKNOWN : keyit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); ++it) {
                    it->second->handleKeyInput(k, InputEnum::ACTION_PRESS);
                }
            } else if (event.type == SDL_KEYUP) {
                keyit = keymap.find(event.key.keysym.sym);
                InputEnum::KeyboardKey k = keyit == keymap.end() ? InputEnum::K_UNKNOWN : keyit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); ++it) {
                    it->second->handleKeyInput(k, InputEnum::ACTION_RELEASE);
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                buttonit = mousebuttonmap.find(event.button.button);
                InputEnum::MouseButton mb = buttonit == mousebuttonmap.end() ? InputEnum::MOUSE_UNKNOWN : buttonit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); ++it) {
                    it->second->handleMouseButtonInput(mb, InputEnum::ACTION_PRESS);
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                buttonit = mousebuttonmap.find(event.button.button);
                InputEnum::MouseButton mb = buttonit == mousebuttonmap.end() ? InputEnum::MOUSE_UNKNOWN : buttonit->second;

                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); ++it) {
                    it->second->handleMouseButtonInput(mb, InputEnum::ACTION_RELEASE);
                }
            } else if (event.type == SDL_MOUSEWHEEL) {
                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); ++it) {
                    it->second->handleMouseScrollInput(event.wheel.x, event.wheel.y);
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                for (it = SDLWindow::windowMap.begin(); it != SDLWindow::windowMap.end(); ++it) {
                    it->second->handleMousePosInput(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                }
            }
		}
		return true;
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

    SDLWindow::SDLWindow() {
        this->window = NULL;
        this->windowWidth = 0;
        this->windowHeight = 0;
        this->windowId = 0;
        this->context = NULL;
    }
}}
