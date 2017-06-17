#include <cstddef>
#include <string>

#include <CSE/CSELL/core/window.hpp>
#include <CSE/CSELL/core/inputcallbackhandler.hpp>

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
    void Window::registerInputCallbackHandler(InputCallbackHandler *cbh) {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return;
        }
        this->callbackHandler = cbh;
    }

    void Window::handleKeyInput(int key, int action, int mods) {
        if (this->callbackHandler == NULL) {
            return;
        }
        this->callbackHandler->handleKeyInput(key, action, mods);
    }

    void Window::handleMousePosInput(double xpos, double ypos) {
        if (this->callbackHandler == NULL) {
            return;
        }
        this->callbackHandler->handleMousePosInput(xpos, ypos);
    }

    void Window::handleMouseButtonInput(int button, int action, int mods) {
        if (this->callbackHandler == NULL) {
            return;
        }
        this->callbackHandler->handleMouseButtonInput(button, action, mods);
    }

    void Window::handleMouseScrollInput(double xoffset, double yoffset) {
        if (this->callbackHandler == NULL) {
            return;
        }
        this->callbackHandler->handleMouseScrollInput(xoffset, yoffset);
    }

    void Window::handleMouseEnterLeaveInput(int entered) {
        if (this->callbackHandler == NULL) {
            return;
        }
        this->callbackHandler->handleMouseEnterLeaveInput(entered);
    }

    void Window::update() {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return;
        }
        this->updateImplementation();
    }

    double Window::getTime() {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return -1.0;
        }
        return this->getTimeImplementation();
    }

    void Window::useContext() {
        if (!this->successfulInit) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Core - Window", "Window is not initialized!");
            return;
        }
        this->useContextImplementation();
    }
}}
