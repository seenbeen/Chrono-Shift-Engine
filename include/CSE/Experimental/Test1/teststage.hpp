#ifndef EXPERIMENTAL_TEST1_TESTSTAGE_HPP
#define EXPERIMENTAL_TEST1_TESTSTAGE_HPP

#include <CSE/CSEA/core/stage.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/orthographiccamera.hpp>

#include <CSE/Experimental/Test1/testgameobject.hpp>

namespace Experimental { namespace Test1 {
    class TestStage : public CSEA::Core::Stage {
        CSEA::Render::Viewport *viewport;
        CSEA::Render::Scene *scene;
        CSEA::Render::OrthographicCamera *camera;

        Experimental::Test1::TestGameObject *testObject;

    protected:
        void onLoad();
        void onUnload();

        void onTransitionInto();
        void onTransitionOutOf();
    public:
        TestStage();
        ~TestStage();
    };
}}
#endif
