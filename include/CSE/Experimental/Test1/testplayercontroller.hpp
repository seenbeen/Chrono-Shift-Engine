#ifndef EXPERIMENTAL_TEST1_TESTPLAYERCONTROLLER_HPP
#define EXPERIMENTAL_TEST1_TESTPLAYERCONTROLLER_HPP

#include <CSE/CSEA/core/controller.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>

#include <CSE/Experimental/Test1/testplayer.hpp>

namespace Experimental { namespace Test1 {
    class TestPlayerController: public CSEA::Core::Controller<TestPlayer>, public CSEA::Input::InputListener {
    protected:
        void onEnter();
        void onExit();
        void onUpdate(double deltaTime);
        void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action);
    };
}}
#endif // EXPERIMENTAL_TEST1_TESTPLAYERCONTROLLER_HPP
