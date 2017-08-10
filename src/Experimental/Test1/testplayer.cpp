#include <CSE/Experimental/Test1/testplayer.hpp>

#include <CSE/CSELL/core/inputenum.hpp>

#include <CSE/CSELL/math/vector3f.hpp>
#include <CSE/CSELL/math/transform.hpp>

#include <CSE/CSEA/input/inputmanager.hpp>

#include <CSE/CSEA/core/gameobject.hpp>
#include <CSE/CSEA/core/stage.hpp>

#include <CSE/CSEA/render/scene.hpp>

#include <CSE/Experimental/Test1/testspriterenderable.hpp>


namespace Experimental { namespace Test1 {
    void TestPlayer::onEnter() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestPlayer", "On Enter.");
        this->gameScene->addRenderable(this->renderable);

        // Register - note that since the stage had to have registered first with
        // TEST_STAGE, we are guaranteed to receive input after the stage
        // has had a chance to process it

        CSEA::Input::InputManager::registerInputListener(this, "TEST_STAGE");
    }

    void TestPlayer::onExit() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestPlayer", "On Exit.");
        CSEA::Input::InputManager::unregisterInputListener(this, "TEST_STAGE");
        this->gameScene->removeRenderable(this->renderable);
    }

    void TestPlayer::onUpdate(double deltaTime) {
        // get a reference to our renderable's transform and apply updates
        // Remember we have dereference in the appropriate places

        CSELL::Math::Transform & xform = *this->renderable->getTransform();
        xform.position += *this->playerDirection * this->playerSpeed * (float)deltaTime; // apply velocity
    }

    TestPlayer::TestPlayer(CSEA::Render::Scene *gameScene) {
        this->renderable = new TestSpriteRenderable(this->STAND_ANIM_KEY);
        this->gameScene = gameScene;
        this->playerDirection = new CSELL::Math::Vector3f();
    }

    TestPlayer::~TestPlayer() {
        delete this->playerDirection;
        delete this->renderable;
    }

    // Input Handling
    void TestPlayer::onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        CSELL::Math::Vector3f &pDir = *this->playerDirection;

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
            this->renderable->setCurrentAnimation(this->WALK_ANIM_KEY);

            // set his direction accordingly
            if (pDir.x > 0.0f) {
                this->renderable->getTransform()->scale.x = -1.0f;
            } else if (pDir.x < 0.0f) {
                this->renderable->getTransform()->scale.x = 1.0f;
            }
        } else {
            this->renderable->setCurrentAnimation(this->STAND_ANIM_KEY);
        }
    }
}}

