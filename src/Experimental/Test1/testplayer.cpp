#include <CSE/Experimental/Test1/testplayer.hpp>

#include <CSE/CSELL/math/vector3f.hpp>
#include <CSE/CSELL/math/transform.hpp>

#include <CSE/CSEA/core/gameobject.hpp>
#include <CSE/CSEA/core/stage.hpp>

#include <CSE/CSEA/render/scene.hpp>

#include <CSE/Experimental/Test1/testspriterenderable.hpp>


namespace Experimental { namespace Test1 {
    void TestPlayer::onEnter() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestPlayer", "On Enter.");
        this->gameScene->addRenderable(this->renderable);
        this->gameScene->addRenderable(this->fRenderable);
    }

    void TestPlayer::onExit() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestPlayer", "On Exit.");
        this->gameScene->removeRenderable(this->fRenderable);
        this->gameScene->removeRenderable(this->renderable);
    }

    void TestPlayer::onUpdate(double deltaTime) {
        // get a reference to our renderable's transform and apply updates
        // Remember we have dereference in the appropriate places
        CSELL::Math::Transform & xform = *this->renderable->getTransform();
        CSELL::Math::Transform & xform2 = *this->fRenderable->getTransform();
        xform.position += *this->playerDirection * this->playerSpeed * (float)deltaTime; // apply velocity
        xform2.position += *this->playerDirection * this->playerSpeed * (float)deltaTime; // apply velocity
    }

    TestPlayer::TestPlayer(CSEA::Render::Scene *gameScene) {
        this->renderable = new TestSpriteRenderable(this->STAND_ANIM_KEY);
        this->fRenderable = new Experimental::FontTest::FontRenderable();
        this->gameScene = gameScene;
        this->playerDirection = new CSELL::Math::Vector3f();
    }

    TestPlayer::~TestPlayer() {
        delete this->playerDirection;
        delete this->renderable;
    }
}}

