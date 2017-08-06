#ifndef EXPERIMENTAL_TEST1_TESTGAMEOBJECT_HPP
#define EXPERIMENTAL_TEST1_TESTGAMEOBJECT_HPP

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/render/renderable.hpp>

#include <CSE/CSEA/core/stage.hpp>
#include <CSE/CSEA/core/gameobject.hpp>

#include <CSE/Experimental/Test1/testrenderable.hpp>

namespace Experimental { namespace Test1 {
    class TestGameObject : public CSEA::Core::GameObject {
        Experimental::Test1::TestRenderable *testRenderable;
        CSEA::Render::Scene *stageScene;

        void onEnter();
        void onExit();
        void onUpdate(double deltaTime);

    public:
        explicit TestGameObject(CSEA::Render::Scene *stageScene, const CSELL::Math::Vector3f &pos);
        ~TestGameObject();
    };
}}
#endif
