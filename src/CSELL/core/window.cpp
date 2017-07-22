#include <string>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>
#include <CSE/CSELL/core/inputenum.hpp>

namespace CSELL { namespace Core {
    Window::~Window() {}

    bool Window::initialize(Window::Settings settings) {
        if (this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is already initialized!");
            return false;
        }
        this->successfulInit = this->initializeImplementation(settings);
        return this->successfulInit;
    }

    void Window::destroy() {
        if (this->successfulInit) {
            this->destroyImplementation();
        }
        delete this;
    }

    /* Input Callback Stuff */
    bool Window::registerInputCallbackHandler(InputCallbackHandler *cbh) {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return false;
        }
        this->callbackHandler = cbh;
        return true;
    }

    bool Window::handleKeyInput(InputEnum::KeyboardKey key, InputEnum::InputAction action) {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleKeyInput(key, action);
        return true;
    }

    bool Window::handleMousePosInput(double xpos, double ypos, double xrel, double yrel) {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleMousePosInput(xpos, ypos, xrel, yrel);
        return true;
    }

    bool Window::handleMouseButtonInput(InputEnum::MouseButton button, InputEnum::InputAction action) {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleMouseButtonInput(button, action);
        return true;
    }

    bool Window::handleMouseScrollInput(double xoffset, double yoffset) {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleMouseScrollInput(xoffset, yoffset);
        return true;
    }

    bool Window::handleMouseEnterLeaveInput(bool entered) {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleMouseEnterLeaveInput(entered);
        return true;
    }

    bool Window::handleWindowResizeInput(unsigned int width, unsigned int height) {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleWindowResizeInput(width, height);
        return true;
    }

    bool Window::handleWindowCloseInput() {
        if (this->callbackHandler == NULL) {
            return false;
        }
        this->callbackHandler->handleWindowCloseInput();
        return true;
    }

    bool Window::update() {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return false;
        }
        return this->updateImplementation();
    }

    double Window::getTime() {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return -1.0;
        }
        return this->getTimeImplementation();
    }

    bool Window::useContext() {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return false;
        }
        return this->useContextImplementation();
    }

    bool Window::setCursorMode(bool enable) {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return false;
        }
        return this-setCursorModeImplementation(enable);
    }
}}
