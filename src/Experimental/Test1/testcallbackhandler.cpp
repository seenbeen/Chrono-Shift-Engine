/*
class TestCallbackHandler : public CSEA::Input::InputListener {
    void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        if (key == CSELL::Core::InputEnum::K_ESCAPE && action == CSELL::Core::InputEnum::ACTION_PRESS) {
            running = false;
        }
        if (key == CSELL::Core::InputEnum::K_SPACE) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                renderer->setPolygonMode(true);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                renderer->setPolygonMode(false);
            }
        }
        if (key == CSELL::Core::InputEnum::K_TAB) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                window->setCursorMode(false);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                window->setCursorMode(true);
            }
        }
    }

    void onMousePosInput(double xpos, double ypos, double xrel, double yrel) {
        //std::cout << xpos << ", " << ypos << " | " << xrel << ", " << yrel << std::endl;
    }

    void onMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action) {
        if (button == CSELL::Core::InputEnum::MOUSE_UNKNOWN) {
            CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSELL, "Main", "Random Mouse Pressed");
        }
    }
    void onMouseScrollInput(double xoffset, double yoffset) {}
    void onMouseEnterLeaveInput(bool entered) {}

    void onWindowResizeInput(unsigned int width, unsigned int height) {
        renderer->setViewport(0, 0, width, height);
    }
    void onWindowCloseInput() {
        running = false;
    };
};
*/
