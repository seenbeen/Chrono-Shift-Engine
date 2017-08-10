#include <CSE/Experimental/Test1/testgameobject.hpp>

#include <string>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/core/stage.hpp>

#include <CSE/CSEA/render/scene.hpp>
#include <CSE/Experimental/Test1/testspriterenderable.hpp>


namespace Experimental { namespace Test1 {
    void TestGameObject::onEnter() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestGameObject", "On Enter.");
        this->stageScene->addRenderable(this->testSpriteRenderable);
    }

    void TestGameObject::onExit() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestGameObject", "On Exit.");
        this->stageScene->removeRenderable(this->testSpriteRenderable);
    }

    void TestGameObject::onUpdate(double deltaTime) {}

    TestGameObject::TestGameObject(CSEA::Render::Scene *stageScene, const std::string &anim, const CSELL::Math::Vector3f &pos) {
        this->testSpriteRenderable = new TestSpriteRenderable(anim);
        this->testSpriteRenderable->getTransform()->position = pos;
        this->stageScene = stageScene;
    }

    TestGameObject::~TestGameObject() {
        delete this->testSpriteRenderable;
    }
}}

