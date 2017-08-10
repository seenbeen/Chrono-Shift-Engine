#ifndef EXPERIMENTAL_TEST1_TESTPLAYER_HPP
#define EXPERIMENTAL_TEST1_TESTPLAYER_HPP

#include <CSE/CSEA/input/inputlistener.hpp>

#include <string>

#include <CSE/CSELL/math/vector3f.hpp>
#include <CSE/CSEA/core/gameobject.hpp>
#include <CSE/CSEA/core/stage.hpp>

#include <CSE/CSEA/render/scene.hpp>

#include <CSE/Experimental/Test1/testspriterenderable.hpp>

/*
    The experimental player class.
    DISCLAIMER: THIS IS AN EXTREMELY OVERSIMPLIFIED CLASS AND IS ONLY USED TO TEST ENGINE FEATURES
*/
namespace Experimental { namespace Test1 {
    class TestPlayer : public CSEA::Core::GameObject, public CSEA::Input::InputListener {
        Experimental::Test1::TestSpriteRenderable *renderable;
        CSEA::Render::Scene *gameScene;

        const std::string STAND_ANIM_KEY = "stand1";
        const std::string WALK_ANIM_KEY = "walk1";

        float playerSpeed = 100.0f;
        CSELL::Math::Vector3f *playerDirection;

        void onEnter();
        void onExit();
        void onUpdate(double deltaTime);

    protected:
        void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action);

    public:
        TestPlayer(CSEA::Render::Scene *stageScene);
        ~TestPlayer();
    };
}}
#endif
