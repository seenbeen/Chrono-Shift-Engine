#include <string>
#include <map>

#include <lib/glad/glad.h>
#include <lib/glfw/glfw3.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/glfwwindow.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>

namespace CSELL { namespace Core {
    static std::map<GLFWwindow *, GlfwWindow *> glfwWindowManager;

    static std::map<int, InputCallbackHandler::KeyboardKey> keymap;

    static std::map<int, InputCallbackHandler::MouseButton> mousebuttonmap;

    static std::map<int, InputCallbackHandler::InputAction> actionmap;

    static struct InitMaps {
        InitMaps() {
            mousebuttonmap[GLFW_MOUSE_BUTTON_LEFT] = CSELL::Core::InputCallbackHandler::MOUSE_LEFT;
            mousebuttonmap[GLFW_MOUSE_BUTTON_MIDDLE] = CSELL::Core::InputCallbackHandler::MOUSE_MIDDLE;
            mousebuttonmap[GLFW_MOUSE_BUTTON_RIGHT] = CSELL::Core::InputCallbackHandler::MOUSE_RIGHT;

            actionmap[GLFW_PRESS] = CSELL::Core::InputCallbackHandler::ACTION_PRESS;
            actionmap[GLFW_RELEASE] = CSELL::Core::InputCallbackHandler::ACTION_RELEASE;

            keymap[GLFW_KEY_0] = CSELL::Core::InputCallbackHandler::K_0;
            keymap[GLFW_KEY_1] = CSELL::Core::InputCallbackHandler::K_1;
            keymap[GLFW_KEY_2] = CSELL::Core::InputCallbackHandler::K_2;
            keymap[GLFW_KEY_3] = CSELL::Core::InputCallbackHandler::K_3;
            keymap[GLFW_KEY_4] = CSELL::Core::InputCallbackHandler::K_4;
            keymap[GLFW_KEY_5] = CSELL::Core::InputCallbackHandler::K_5;
            keymap[GLFW_KEY_6] = CSELL::Core::InputCallbackHandler::K_6;
            keymap[GLFW_KEY_7] = CSELL::Core::InputCallbackHandler::K_7;
            keymap[GLFW_KEY_8] = CSELL::Core::InputCallbackHandler::K_8;
            keymap[GLFW_KEY_9] = CSELL::Core::InputCallbackHandler::K_9;
            keymap[GLFW_KEY_A] = CSELL::Core::InputCallbackHandler::K_A;
            keymap[GLFW_KEY_B] = CSELL::Core::InputCallbackHandler::K_B;
            keymap[GLFW_KEY_C] = CSELL::Core::InputCallbackHandler::K_C;
            keymap[GLFW_KEY_D] = CSELL::Core::InputCallbackHandler::K_D;
            keymap[GLFW_KEY_E] = CSELL::Core::InputCallbackHandler::K_E;
            keymap[GLFW_KEY_F] = CSELL::Core::InputCallbackHandler::K_F;
            keymap[GLFW_KEY_G] = CSELL::Core::InputCallbackHandler::K_G;
            keymap[GLFW_KEY_H] = CSELL::Core::InputCallbackHandler::K_H;
            keymap[GLFW_KEY_I] = CSELL::Core::InputCallbackHandler::K_I;
            keymap[GLFW_KEY_J] = CSELL::Core::InputCallbackHandler::K_J;
            keymap[GLFW_KEY_K] = CSELL::Core::InputCallbackHandler::K_K;
            keymap[GLFW_KEY_L] = CSELL::Core::InputCallbackHandler::K_L;
            keymap[GLFW_KEY_M] = CSELL::Core::InputCallbackHandler::K_M;
            keymap[GLFW_KEY_N] = CSELL::Core::InputCallbackHandler::K_N;
            keymap[GLFW_KEY_O] = CSELL::Core::InputCallbackHandler::K_O;
            keymap[GLFW_KEY_P] = CSELL::Core::InputCallbackHandler::K_P;
            keymap[GLFW_KEY_Q] = CSELL::Core::InputCallbackHandler::K_Q;
            keymap[GLFW_KEY_R] = CSELL::Core::InputCallbackHandler::K_R;
            keymap[GLFW_KEY_S] = CSELL::Core::InputCallbackHandler::K_S;
            keymap[GLFW_KEY_T] = CSELL::Core::InputCallbackHandler::K_T;
            keymap[GLFW_KEY_U] = CSELL::Core::InputCallbackHandler::K_U;
            keymap[GLFW_KEY_V] = CSELL::Core::InputCallbackHandler::K_V;
            keymap[GLFW_KEY_W] = CSELL::Core::InputCallbackHandler::K_W;
            keymap[GLFW_KEY_X] = CSELL::Core::InputCallbackHandler::K_X;
            keymap[GLFW_KEY_Y] = CSELL::Core::InputCallbackHandler::K_Y;
            keymap[GLFW_KEY_Z] = CSELL::Core::InputCallbackHandler::K_Z;
            keymap[GLFW_KEY_SPACE] = CSELL::Core::InputCallbackHandler::K_SPACE;
            keymap[GLFW_KEY_EQUAL] = CSELL::Core::InputCallbackHandler::K_EQUAL;
            keymap[GLFW_KEY_APOSTROPHE] = CSELL::Core::InputCallbackHandler::K_APOSTROPHE;
            keymap[GLFW_KEY_PERIOD] = CSELL::Core::InputCallbackHandler::K_PERIOD;
            keymap[GLFW_KEY_COMMA] = CSELL::Core::InputCallbackHandler::K_COMMA;
            keymap[GLFW_KEY_MINUS] = CSELL::Core::InputCallbackHandler::K_MINUS;
            keymap[GLFW_KEY_SLASH] = CSELL::Core::InputCallbackHandler::K_SLASH;
            keymap[GLFW_KEY_BACKSLASH] = CSELL::Core::InputCallbackHandler::K_BACKSLASH;
            keymap[GLFW_KEY_SEMICOLON] = CSELL::Core::InputCallbackHandler::K_SEMICOLON;
            keymap[GLFW_KEY_LEFT_BRACKET] = CSELL::Core::InputCallbackHandler::K_LBRACK;
            keymap[GLFW_KEY_RIGHT_BRACKET] = CSELL::Core::InputCallbackHandler::K_RBRACK;

            keymap[GLFW_KEY_GRAVE_ACCENT] = CSELL::Core::InputCallbackHandler::K_BACKTICK;

            keymap[GLFW_KEY_LEFT_CONTROL] = CSELL::Core::InputCallbackHandler::K_LCTRL;
            keymap[GLFW_KEY_RIGHT_CONTROL] = CSELL::Core::InputCallbackHandler::K_RCTRL;
            keymap[GLFW_KEY_LEFT_ALT] = CSELL::Core::InputCallbackHandler::K_LALT;
            keymap[GLFW_KEY_RIGHT_ALT] = CSELL::Core::InputCallbackHandler::K_RALT;
            keymap[GLFW_KEY_LEFT_SHIFT] = CSELL::Core::InputCallbackHandler::K_LSHIFT;
            keymap[GLFW_KEY_RIGHT_SHIFT] = CSELL::Core::InputCallbackHandler::K_RSHIFT;

            keymap[GLFW_KEY_UP] = CSELL::Core::InputCallbackHandler::K_UP;
            keymap[GLFW_KEY_DOWN] = CSELL::Core::InputCallbackHandler::K_DOWN;
            keymap[GLFW_KEY_LEFT] = CSELL::Core::InputCallbackHandler::K_LEFT;
            keymap[GLFW_KEY_RIGHT] = CSELL::Core::InputCallbackHandler::K_RIGHT;

            keymap[GLFW_KEY_ESCAPE] = CSELL::Core::InputCallbackHandler::K_ESCAPE;
            keymap[GLFW_KEY_ENTER] = CSELL::Core::InputCallbackHandler::K_ENTER;
            keymap[GLFW_KEY_TAB] = CSELL::Core::InputCallbackHandler::K_TAB;
            keymap[GLFW_KEY_BACKSPACE] = CSELL::Core::InputCallbackHandler::K_BACKSPACE;
            keymap[GLFW_KEY_INSERT] = CSELL::Core::InputCallbackHandler::K_INSERT;
            keymap[GLFW_KEY_DELETE] = CSELL::Core::InputCallbackHandler::K_DELETE;
            keymap[GLFW_KEY_HOME] = CSELL::Core::InputCallbackHandler::K_HOME;
            keymap[GLFW_KEY_END] = CSELL::Core::InputCallbackHandler::K_END;
            keymap[GLFW_KEY_PAGE_UP] = CSELL::Core::InputCallbackHandler::K_PAGEUP;
            keymap[GLFW_KEY_PAGE_DOWN] = CSELL::Core::InputCallbackHandler::K_PAGEDOWN;

            keymap[GLFW_KEY_CAPS_LOCK] = CSELL::Core::InputCallbackHandler::K_CAPSLOCK;
            keymap[GLFW_KEY_SCROLL_LOCK] = CSELL::Core::InputCallbackHandler::K_SCROLLLOCK;
            keymap[GLFW_KEY_NUM_LOCK] = CSELL::Core::InputCallbackHandler::K_NUMLOCK;

            keymap[GLFW_KEY_PRINT_SCREEN] = CSELL::Core::InputCallbackHandler::K_PRINTSCREEN;
            keymap[GLFW_KEY_PAUSE] = CSELL::Core::InputCallbackHandler::K_PAUSE;

            keymap[GLFW_KEY_F1] = CSELL::Core::InputCallbackHandler::K_F1;
            keymap[GLFW_KEY_F2] = CSELL::Core::InputCallbackHandler::K_F2;
            keymap[GLFW_KEY_F3] = CSELL::Core::InputCallbackHandler::K_F3;
            keymap[GLFW_KEY_F4] = CSELL::Core::InputCallbackHandler::K_F4;
            keymap[GLFW_KEY_F5] = CSELL::Core::InputCallbackHandler::K_F5;
            keymap[GLFW_KEY_F6] = CSELL::Core::InputCallbackHandler::K_F6;
            keymap[GLFW_KEY_F7] = CSELL::Core::InputCallbackHandler::K_F7;
            keymap[GLFW_KEY_F8] = CSELL::Core::InputCallbackHandler::K_F8;
            keymap[GLFW_KEY_F9] = CSELL::Core::InputCallbackHandler::K_F9;
            keymap[GLFW_KEY_F10] = CSELL::Core::InputCallbackHandler::K_F10;
            keymap[GLFW_KEY_F11] = CSELL::Core::InputCallbackHandler::K_F11;
            keymap[GLFW_KEY_F12] = CSELL::Core::InputCallbackHandler::K_F12;

            keymap[GLFW_KEY_KP_0] = CSELL::Core::InputCallbackHandler::K_KEYPAD_0;
            keymap[GLFW_KEY_KP_1] = CSELL::Core::InputCallbackHandler::K_KEYPAD_1;
            keymap[GLFW_KEY_KP_2] = CSELL::Core::InputCallbackHandler::K_KEYPAD_2;
            keymap[GLFW_KEY_KP_3] = CSELL::Core::InputCallbackHandler::K_KEYPAD_3;
            keymap[GLFW_KEY_KP_4] = CSELL::Core::InputCallbackHandler::K_KEYPAD_4;
            keymap[GLFW_KEY_KP_5] = CSELL::Core::InputCallbackHandler::K_KEYPAD_5;
            keymap[GLFW_KEY_KP_6] = CSELL::Core::InputCallbackHandler::K_KEYPAD_6;
            keymap[GLFW_KEY_KP_7] = CSELL::Core::InputCallbackHandler::K_KEYPAD_7;
            keymap[GLFW_KEY_KP_8] = CSELL::Core::InputCallbackHandler::K_KEYPAD_8;
            keymap[GLFW_KEY_KP_9] = CSELL::Core::InputCallbackHandler::K_KEYPAD_9;

            keymap[GLFW_KEY_KP_DIVIDE] = CSELL::Core::InputCallbackHandler::K_KEYPAD_DIVIDE;
            keymap[GLFW_KEY_KP_MULTIPLY] = CSELL::Core::InputCallbackHandler::K_KEYBOARD_MULTIPLY;
            keymap[GLFW_KEY_KP_ADD] = CSELL::Core::InputCallbackHandler::K_KEYPAD_ADD;
            keymap[GLFW_KEY_KP_SUBTRACT] = CSELL::Core::InputCallbackHandler::K_KEYPAD_SUBTRACT;

            keymap[GLFW_KEY_KP_DECIMAL] = CSELL::Core::InputCallbackHandler::K_KEYPAD_DECIMAL;
            keymap[GLFW_KEY_KP_ENTER] = CSELL::Core::InputCallbackHandler::K_KEYPAD_ENTER;
            keymap[GLFW_KEY_KP_EQUAL] = CSELL::Core::InputCallbackHandler::K_KEYPAD_EQUAL;
        }
    } initMaps;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        std::map<int, InputCallbackHandler::KeyboardKey>::iterator keyit;
        std::map<int, InputCallbackHandler::InputAction>::iterator actionit;
        keyit = keymap.find(key);
        actionit = actionmap.find(action);

        InputCallbackHandler::KeyboardKey k = keyit == keymap.end() ? InputCallbackHandler::K_UNKNOWN : keyit->second;
        InputCallbackHandler::InputAction a = actionit == actionmap.end() ? InputCallbackHandler::ACTION_UNKNOWN : actionit->second;

        glfwWindowManager.find(window)->second->handleKeyInput(k, a);
    }

    static void mousePosCallback(GLFWwindow *window, double xpos, double ypos) {
        glfwWindowManager.find(window)->second->handleMousePosInput(xpos, ypos);
    }

    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        std::map<int, InputCallbackHandler::MouseButton>::iterator buttonit;
        std::map<int, InputCallbackHandler::InputAction>::iterator actionit;
        buttonit = mousebuttonmap.find(button);
        actionit = actionmap.find(action);

        InputCallbackHandler::MouseButton mb = buttonit == mousebuttonmap.end() ? InputCallbackHandler::MOUSE_UNKNOWN : buttonit->second;
        InputCallbackHandler::InputAction a = actionit == actionmap.end() ? InputCallbackHandler::ACTION_UNKNOWN : actionit->second;

        glfwWindowManager.find(window)->second->handleMouseButtonInput(mb, a);
    }

    static void mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
        glfwWindowManager.find(window)->second->handleMouseScrollInput(xoffset, yoffset);
    }

    static void mouseEnterLeaveCallback(GLFWwindow *window, int entered) {
        glfwWindowManager.find(window)->second->handleMouseEnterLeaveInput(entered == 1);
    }

    static void windowResizeCallback(GLFWwindow *window, int width, int height) {
        glfwWindowManager.find(window)->second->handleWindowResizeInput(width, height);
    }

    static void windowCloseCallback(GLFWwindow *window) {
        glfwWindowManager.find(window)->second->handleWindowCloseInput();
    }

    bool GlfwWindow::initializeImplementation(Window::Settings settings) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, settings.resizeable);

        this->windowWidth = settings.width;
        this->windowHeight = settings.height;
        this->windowTitle = settings.title;

        // Set up GL Window

        this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowTitle.c_str(), NULL, NULL);

        if (this->window == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "RenderEngine", "GLFW Unable to create window!");
            return false;
        }

        glfwMakeContextCurrent(this->window);


        // Set up glad loader to load in gl procs
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "RenderEngine", "Failed to initialize GLAD!");
            return false;
        }

        glfwWindowManager[this->window] = this;

        glfwSetKeyCallback(this->window, keyCallback);
        glfwSetCursorPosCallback(this->window, mousePosCallback);
        glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
        glfwSetScrollCallback(this->window, mouseScrollCallback);
        glfwSetCursorEnterCallback(this->window, mouseEnterLeaveCallback);
        glfwSetWindowCloseCallback(this->window, windowCloseCallback);
        glfwSetWindowSizeCallback(this->window, windowResizeCallback);

        return true;
    }

    void GlfwWindow::destroyImplementation() {
        glfwWindowManager.erase(glfwWindowManager.find(this->window));
        glfwDestroyWindow(window);
    }

    void GlfwWindow::updateImplementation() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    double GlfwWindow::getTimeImplementation() {
        return glfwGetTime();
    }

    void GlfwWindow::useContextImplementation() {
        glfwMakeContextCurrent(this->window);
    }
}}
