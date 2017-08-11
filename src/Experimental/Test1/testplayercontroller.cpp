#include <CSE/Experimental/Test1/testplayercontroller.hpp>

#include <CSE/CSELL/core/inputenum.hpp>
#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/core/controller.hpp>

#include <CSE/CSEA/input/inputmanager.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>

#include <CSE/Experimental/Test1/testplayer.hpp>

namespace Experimental { namespace Test1 {
    void TestPlayerController::onEnter() {
        // Register - note that since the stage had to have registered first with
        // TEST_STAGE, we are guaranteed to receive input after the stage
        // has had a chance to process it
        CSEA::Input::InputManager::registerInputListener(this, "TEST_STAGE");
    }

    void TestPlayerController::onExit() {
        CSEA::Input::InputManager::unregisterInputListener(this, "TEST_STAGE");
    }

    void TestPlayerController::onUpdate(double deltaTime) {

    }

    void TestPlayerController::onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        // get reference to player
        TestPlayer &player = *this->gameObject;

        CSELL::Math::Vector3f &pDir = *player.playerDirection;

        if (key == CSELL::Core::InputEnum::K_W) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                pDir += CSELL::Math::Vector3f(0.0f, 1.0f, 0.0f);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                pDir -= CSELL::Math::Vector3f(0.0f, 1.0f, 0.0f);
            }
        }

        if (key == CSELL::Core::InputEnum::K_S) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                pDir += CSELL::Math::Vector3f(0.0f, -1.0f, 0.0f);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                pDir -= CSELL::Math::Vector3f(0.0f, -1.0f, 0.0f);
            }
        }

        if (key == CSELL::Core::InputEnum::K_A) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                pDir += CSELL::Math::Vector3f(-1.0f, 0.0f, 0.0f);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                pDir -= CSELL::Math::Vector3f(-1.0f, 0.0f, 0.0f);
            }
        }

        if (key == CSELL::Core::InputEnum::K_D) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                pDir += CSELL::Math::Vector3f(1.0f, 0.0f, 0.0f);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                pDir -= CSELL::Math::Vector3f(1.0f, 0.0f, 0.0f);
            }
        }

        // change our animation accordingly
        if (pDir.magnitudeSquared() != 0.0f) {
            player.renderable->setCurrentAnimation(player.WALK_ANIM_KEY);

            // set his direction accordingly
            if (pDir.x > 0.0f) {
                player.renderable->getTransform()->scale.x = -1.0f;
            } else if (pDir.x < 0.0f) {
                player.renderable->getTransform()->scale.x = 1.0f;
            }
        } else {
            player.renderable->setCurrentAnimation(player.STAND_ANIM_KEY);
        }
    }
}}
