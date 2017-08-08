#include <CSE/CSEA/input/inputlistener.hpp>

#include <CSE/CSELL/core/inputenum.hpp>

namespace CSEA { namespace Input {
    void InputListener::onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {}
    void InputListener::onMousePosInput(double xpos, double ypos, double xrel, double yrel) {}
    void InputListener::onMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action) {}
    void InputListener::onMouseScrollInput(double xoffset, double yoffset) {}
    void InputListener::onMouseEnterLeaveInput(bool entered) {}

    void InputListener::onWindowResizeInput(unsigned int width, unsigned int height) {}
    void InputListener::onWindowCloseInput() {}

    InputListener::InputListener() {
        this->isEnabled = true;
    }

    void InputListener::setListenerIsEnabled(bool isEnabled) {
        this->isEnabled = isEnabled;
    }
}}
