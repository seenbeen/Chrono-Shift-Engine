#ifndef EXPERIMENTAL_TEST1_TESTGAMEOBJECT_HPP
#define EXPERIMENTAL_TEST1_TESTGAMEOBJECT_HPP

#include <string>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/render/renderable.hpp>

#include <CSE/CSEA/core/stage.hpp>
#include <CSE/CSEA/core/gameobject.hpp>

#include <CSE/Experimental/Test1/testspriterenderable.hpp>

namespace Experimental { namespace Test1 {
    class TestGameObject : public CSEA::Core::GameObject {
        Experimental::Test1::TestSpriteRenderable *testSpriteRenderable;
        CSEA::Render::Scene *stageScene;

        void onEnter();
        void onExit();
        void onUpdate(double deltaTime);

    public:
        TestGameObject(CSEA::Render::Scene *stageScene, const std::string &anim, const CSELL::Math::Vector3f &pos);
        ~TestGameObject();
    };
}}
#endif
