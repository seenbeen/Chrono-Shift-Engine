#ifndef EXPERIMENTAL_TEST1_TESTSTAGE_HPP
#define EXPERIMENTAL_TEST1_TESTSTAGE_HPP

#include <CSE/CSEA/core/stage.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/scenemanager.hpp>
#include <CSE/CSEA/render/camera.hpp>

#include <CSE/Experimental/Test1/testgameobject.hpp>

namespace Experimental { namespace Test1 {
    class TestStage : public CSEA::Core::Stage, public CSEA::Input::InputListener {
        unsigned int walk1_frames[4] = {0, 1, 2, 3};
        int walk1_originXs[4] = {70, 70, 70, 70};
        int walk1_originYs[4] = {75, 75, 75, 75};
        float walk1_delays[4] = {0.1800f, 0.1800f, 0.1800f, 0.1800f};
        unsigned int stand1_frames[5] = {4, 5, 6, 7, 8};
        int stand1_originXs[5] = {67, 67, 67, 67, 67};
        int stand1_originYs[5] = {75, 75, 75, 75, 75};
        float stand1_delays[5] = {0.5000f, 0.5000f, 0.5000f, 0.5000f, 0.5000f};
        unsigned int alert_frames[5] = {9, 10, 11, 12, 13};
        int alert_originXs[5] = {80, 80, 80, 80, 80};
        int alert_originYs[5] = {74, 74, 74, 74, 74};
        float alert_delays[5] = {0.5000f, 0.5000f, 0.5000f, 0.5000f, 0.5000f};
        unsigned int swingO1_frames[3] = {14, 15, 16};
        int swingO1_originXs[3] = {68, 68, 68};
        int swingO1_originYs[3] = {106, 106, 106};
        float swingO1_delays[3] = {0.3000f, 0.1500f, 0.3500f};
        unsigned int swingO2_frames[3] = {17, 18, 19};
        int swingO2_originXs[3] = {63, 63, 63};
        int swingO2_originYs[3] = {86, 86, 86};
        float swingO2_delays[3] = {0.3000f, 0.1500f, 0.3500f};
        unsigned int swingO3_frames[3] = {20, 21, 22};
        int swingO3_originXs[3] = {121, 121, 121};
        int swingO3_originYs[3] = {101, 101, 101};
        float swingO3_delays[3] = {0.3000f, 0.1500f, 0.3500f};
        unsigned int swingOF_frames[4] = {23, 24, 25, 26};
        int swingOF_originXs[4] = {108, 108, 108, 108};
        int swingOF_originYs[4] = {94, 94, 94, 94};
        float swingOF_delays[4] = {0.2000f, 0.1000f, 0.1000f, 0.3000f};
        unsigned int stabO1_frames[2] = {27, 28};
        int stabO1_originXs[2] = {116, 116};
        int stabO1_originYs[2] = {72, 72};
        float stabO1_delays[2] = {0.3500f, 0.4500f};
        unsigned int stabO2_frames[2] = {29, 30};
        int stabO2_originXs[2] = {115, 115};
        int stabO2_originYs[2] = {75, 75};
        float stabO2_delays[2] = {0.3500f, 0.4500f};
        unsigned int stabOF_frames[3] = {31, 32, 33};
        int stabOF_originXs[3] = {144, 144, 144};
        int stabOF_originYs[3] = {73, 73, 73};
        float stabOF_delays[3] = {0.2500f, 0.1500f, 0.3000f};
        unsigned int proneStab_frames[2] = {34, 35};
        int proneStab_originXs[2] = {112, 112};
        int proneStab_originYs[2] = {47, 47};
        float proneStab_delays[2] = {0.3000f, 0.4000f};
        unsigned int prone_frames[1] = {36};
        int prone_originXs[1] = {90};
        int prone_originYs[1] = {47};
        float prone_delays[1] = {0.1000f};
        unsigned int heal_frames[3] = {37, 38, 39};
        int heal_originXs[3] = {80, 80, 80};
        int heal_originYs[3] = {86, 86, 86};
        float heal_delays[3] = {0.3000f, 0.1500f, 0.3500f};
        unsigned int fly_frames[2] = {40, 41};
        int fly_originXs[2] = {35, 35};
        int fly_originYs[2] = {90, 90};
        float fly_delays[2] = {0.3000f, 0.3000f};
        unsigned int jump_frames[1] = {42};
        int jump_originXs[1] = {35};
        int jump_originYs[1] = {82};
        float jump_delays[1] = {0.2000f};
        unsigned int sit_frames[1] = {43};
        int sit_originXs[1] = {32};
        int sit_originYs[1] = {71};
        float sit_delays[1] = {0.1000f};
        unsigned int ladder_frames[2] = {44, 45};
        int ladder_originXs[2] = {26, 26};
        int ladder_originYs[2] = {73, 73};
        float ladder_delays[2] = {0.2500f, 0.2500f};
        unsigned int rope_frames[2] = {46, 47};
        int rope_originXs[2] = {24, 24};
        int rope_originYs[2] = {76, 76};
        float rope_delays[2] = {0.2500f, 0.2500f};

        CSEA::Render::Viewport *viewport;
        CSEA::Render::Scene *scene;
        CSEA::Render::SceneManager *sceneManager;
        CSEA::Render::Camera *camera;

        Experimental::Test1::TestGameObject *testObject1, *testObject2, *testObject3;

    protected:
        void onLoad();
        void onUnload();

        void onTransitionInto();
        void onTransitionOutOf();

        // input stuff
        void onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action);
        void onWindowResizeInput(unsigned int width, unsigned int height);
        void onWindowCloseInput();

    public:
        TestStage();
        ~TestStage();

    };
}}
#endif
