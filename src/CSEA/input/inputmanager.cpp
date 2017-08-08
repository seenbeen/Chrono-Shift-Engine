#include <CSE/CSEA/input/inputmanager.hpp>
#include <algorithm>
#include <map>
#include <list>
#include <string>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/inputenum.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>

namespace CSEA { namespace Input {
    InputManager *InputManager::instance = NULL;

    bool InputManager::initialize() {
        if (InputManager::instance != NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Input - InputManager",
                             "InputManager already initialized!");
            return false;
        }
        InputManager::instance = new InputManager();
        return true;
    }

    void InputManager::shutdown() {
        if (InputManager::instance == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Input - InputManager",
                             "InputManager not initialized!");
            return;
        }
        delete InputManager::instance;
        InputManager::instance = NULL;
    }

    bool InputManager::registerInputListener(InputListener *listener, const std::string &inputGroup) {
        if (InputManager::instance == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Input - InputManager",
                             "InputManager not initialized!");
            return false;
        }
        return InputManager::instance->onRegisterInputListener(listener, inputGroup);
    }

    bool InputManager::unregisterInputListener(InputListener *listener, const std::string &inputGroup) {
        if (InputManager::instance == NULL) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Input - InputManager",
                             "InputManager not initialized!");
            return false;
        }
        return InputManager::instance->onUnregisterInputListener(listener, inputGroup);
    }

    InputManager::InputManager() {

    }

    InputManager::~InputManager() {

    }

    // registry functions

    bool InputManager::onRegisterInputListener(InputListener *listener, const std::string &inputGroup) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        groupIt = this->inputGroupMap.find(inputGroup);
        if (groupIt == this->inputGroupMap.end()){
            this->inputGroupMap[inputGroup] = std::list<InputListener*>();
            this->inputGroupMap.find(inputGroup)->second.push_back(listener);
            return true;
        } else {
            std::list<InputListener*>::iterator listenerIt;
            listenerIt = std::find(groupIt->second.begin(), groupIt->second.end(), listener);
            if (listenerIt == groupIt->second.end()) {
                groupIt->second.push_back(listener);
                return true;
            }
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                            "Input - InputManager",
                            "Listener already registered to group \"" + inputGroup + "\".");
            return false;
        }
    }

    bool InputManager::onUnregisterInputListener(InputListener *listener, const std::string &inputGroup) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        groupIt = this->inputGroupMap.find(inputGroup);

        if (groupIt == this->inputGroupMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                             "Input - InputManager",
                             "Trying to remove listener from non-existent group \"" + inputGroup + "\".");
            return false;
        }

        std::list<InputListener*>::iterator listenerIt;
        listenerIt = std::find(groupIt->second.begin(), groupIt->second.end(), listener);
        if (listenerIt != groupIt->second.end()) {
            groupIt->second.erase(listenerIt);
            return true;
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA,
                         "Input - InputManager",
                         "Trying to remove non-existent listener from group \"" + inputGroup + "\".");
        return false;
    }

    // own dispatchers
    void InputManager::handleKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onKeyInput(key, action);
                }
            }
        }
    }

    void InputManager::handleMousePosInput(double xpos, double ypos, double xrel, double yrel) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onMousePosInput(xpos, ypos, xrel, yrel);
                }
            }
        }
    }

    void InputManager::handleMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onMouseButtonInput(button, action);
                }
            }
        }
    }

    void InputManager::handleMouseScrollInput(double xoffset, double yoffset) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onMouseScrollInput(xoffset, yoffset);
                }
            }
        }
    }

    void InputManager::handleMouseEnterLeaveInput(bool entered) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onMouseEnterLeaveInput(entered);
                }
            }
        }
    }

    void InputManager::handleWindowResizeInput(unsigned int width, unsigned int height) {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onWindowResizeInput(width, height);
                }
            }
        }
    }

    void InputManager::handleWindowCloseInput() {
        std::map<std::string,std::list<InputListener*>>::iterator groupIt;
        std::list<InputListener*>::iterator listenerIt;
        for (groupIt = this->inputGroupMap.begin(); groupIt != this->inputGroupMap.end(); ++groupIt) {
            for (listenerIt = groupIt->second.begin(); listenerIt != groupIt->second.end(); ++listenerIt) {
                if ((*listenerIt)->isEnabled) {
                    (*listenerIt)->onWindowCloseInput();
                }
            }
        }
    }
}}
