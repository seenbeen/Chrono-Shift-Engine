#include <CSE/Experimental/Test1/testgameobject.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/core/stage.hpp>
#include <CSE/CSEA/core/gameobject.hpp>

#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/scene.hpp>

namespace Experimental { namespace Test1 {
    void TestGameObject::onEnter() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestGameObject", "On Enter.");
        this->stageScene->addRenderable(this->testRenderable);
    }

    void TestGameObject::onExit() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestGameObject", "On Exit.");
        this->stageScene->removeRenderable(this->testRenderable);
    }

    void TestGameObject::onUpdate(double deltaTime) {
        // apply our transform, then replicate it to our renderable.
    }

    TestGameObject::TestGameObject(CSEA::Render::Scene *stageScene, const CSELL::Math::Vector3f &pos) {
        this->testRenderable = new TestSpriteRenderable(pos);
        this->stageScene = stageScene;
    }

    TestGameObject::~TestGameObject() {
        delete this->testRenderable;
    }
}}

