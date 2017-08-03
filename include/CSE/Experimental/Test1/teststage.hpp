#ifndef EXPERIMENTAL_TEST1_TESTSTAGE_HPP
#define EXPERIMENTAL_TEST1_TESTSTAGE_HPP

#include <CSE/CSEA/core/stage.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/orthographiccamera.hpp>

#include <CSE/Experimental/Test1/testgameobject.hpp>

namespace Experimental { namespace Test1 {
    class TestStage : public CSEA::Core::Stage, public CSEA::Input::InputListener {
        CSEA::Render::Viewport *viewport;
        CSEA::Render::Scene *scene;
        CSEA::Render::OrthographicCamera *camera;

        Experimental::Test1::TestGameObject *testObject;

    protected:
        void onLoad();
        void onUnload();

        void onTransitionInto();
        void onTransitionOutOf();

        // input stuff
        void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action);
        void onMousePosInput(double xpos, double ypos, double xrel, double yrel);
        void onMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action);
        void onMouseScrollInput(double xoffset, double yoffset);
        void onMouseEnterLeaveInput(bool entered);
        void onWindowResizeInput(unsigned int width, unsigned int height);
        void onWindowCloseInput();

    public:
        TestStage();
        ~TestStage();

    };
}}
#endif
