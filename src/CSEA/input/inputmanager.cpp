#include <set>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/inputenum.hpp>

#include <CSE/CSEA/input/inputmanager.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>

namespace CSEA { namespace Input {
    InputManager::InputManager() {

    }

    InputManager::~InputManager() {

    }

    // registry functions

    bool InputManager::registerInputListener(InputListener *listener) {
        std::set<InputListener*>::iterator it;
        it = listeners.find(listener);
        if (it == listeners.end()) {
            listeners.insert(listener);
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                        "Input - InputManager",
                        "Trying to register already registered input listener.");
        return false;
    }

    bool InputManager::unregisterInputListener(InputListener *listener) {
        std::set<InputListener*>::iterator it;
        it = listeners.find(listener);
        if (it != listeners.end()) {
            listeners.erase(it);
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                        "Input - InputManager",
                        "Trying to unregister non-registered input listener.");
        return false;
    }

    // own dispatchers
    void InputManager::handleKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onKeyInput(key, action);
        }
    }

    void InputManager::handleMousePosInput(double xpos, double ypos, double xrel, double yrel) {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onMousePosInput(xpos, ypos, xrel, yrel);
        }
    }

    void InputManager::handleMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action) {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onMouseButtonInput(button, action);
        }
    }

    void InputManager::handleMouseScrollInput(double xoffset, double yoffset) {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onMouseScrollInput(xoffset, yoffset);
        }
    }

    void InputManager::handleMouseEnterLeaveInput(bool entered) {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onMouseEnterLeaveInput(entered);
        }
    }

    void InputManager::handleWindowResizeInput(unsigned int width, unsigned int height) {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onWindowResizeInput(width, height);
        }
    }

    void InputManager::handleWindowCloseInput() {
        std::set<InputListener*>::iterator it;
        for (it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->onWindowCloseInput();
        }
    }
}}
