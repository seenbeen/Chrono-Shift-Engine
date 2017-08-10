#include <CSE/Experimental/Test1/teststage.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/asset/assetmanager.hpp>

#include <CSE/CSEA/core/engine.hpp>
#include <CSE/CSEA/core/stage.hpp>

#include <CSE/CSEA/input/inputmanager.hpp>
#include <CSE/CSEA/input/inputlistener.hpp>

#include <CSE/CSEA/render/renderer.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/scene.hpp>

#include <CSE/CSEA/render/scenemanager2d.hpp>
#include <CSE/CSEA/render/scenemanagerui.hpp>

#include <CSE/CSEA/render/uicamera.hpp>
#include <CSE/CSEA/render/orthographiccamera.hpp>

#include <CSE/CSEA/asset/spriteanimationset.hpp>

#include <CSE/Experimental/Test1/testgameobject.hpp>
#include <CSE/Experimental/Test1/testplayer.hpp>

namespace Experimental { namespace Test1 {
    TestStage::TestStage() {
        // setting up our ui
        this->uiViewport = new CSEA::Render::Viewport(0, 0, 800, 600); // (0,0) = bottom left corner of window
        this->uiSceneManager = new CSEA::Render::SceneManagerUI();
        this->uiScene = new CSEA::Render::Scene(this->uiSceneManager);
        this->uiCam = new CSEA::Render::UICamera(800, 600); // 800x600 viewport, coincidentally same as our window

        // attach our ui scene + camera to our viewport
        this->uiViewport->bindCamera(this->uiCam);
        this->uiViewport->bindScene(this->uiScene);

        // setting up our game scene
        this->gameViewport = new CSEA::Render::Viewport(0, 0, 800, 600);
        this->gameSceneManager = new CSEA::Render::SceneManager2D();
        this->gameScene = new CSEA::Render::Scene(this->gameSceneManager);
        this->gameCam = new CSEA::Render::OrthographicCamera(-400, 400, -300, 300, -1, 0);
        // don't worry too much about the ortho cam params - I'll explain them when I get a chance
        // DO NOTE: only objects with Z = [0, 1] will be rendered

        // attach our game scene + camera to our viewport
        this->uiViewport->bindCamera(this->gameCam);
        this->uiViewport->bindScene(this->gameScene);

        // Setting up the game objects
        CSELL::Math::Transform xform; // a transform is a (position, orientation, scale)

        xform.position = CSELL::Math::Vector3f(25.0f, 25.0f, 0.0f);
        this->testObject1 = new Experimental::Test1::TestGameObject(this->gameScene, "stand1", xform.position);
        xform.position = CSELL::Math::Vector3f(-25.0f, -25.0f, 0.0f);
        this->testObject2 = new Experimental::Test1::TestGameObject(this->gameScene, "stand1", xform.position);

        this->testPlayer = new Experimental::Test1::TestPlayer(this->gameScene);
    }

    TestStage::~TestStage() {
        // cleanup allocated memory, in reverse order of allocation
        delete this->testPlayer;
        delete this->testObject2;
        delete this->testObject1;

        delete this->gameCam;
        delete this->gameScene;
        delete this->gameSceneManager;
        delete this->gameViewport;

        delete this->uiCam;
        delete this->uiScene;
        delete this->uiSceneManager;
        delete this->uiViewport;
    }

    void TestStage::onLoad() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Loading");

        // load sprite assets in
        CSEA::Assets::AssetManager::loadFile("assets/test1/fragmentShader.fs");
        CSEA::Assets::AssetManager::loadFile("assets/test1/vertexShader.vs");
        CSEA::Assets::AssetManager::loadImage("assets/test1/toruSheet.png");

        // load sprite animation set in
        CSEA::Assets::SpriteAnimationSet *animSet;
        animSet = CSEA::Assets::AssetManager::loadSpriteAnimationSet("assets/test1/toruAnimSet.xml");

        // should be loaded in the above call by a loader in the future
        animSet->addAnimation("walk1", 4, this->walk1_frames, this->walk1_originXs, this->walk1_originYs, this->walk1_delays);
        animSet->addAnimation("stand1", 5, this->stand1_frames, this->stand1_originXs, this->stand1_originYs, this->stand1_delays);
        animSet->addAnimation("alert", 5, this->alert_frames, this->alert_originXs, this->alert_originYs, this->alert_delays);
        animSet->addAnimation("swingO1", 3, this->swingO1_frames, this->swingO1_originXs, this->swingO1_originYs, this->swingO1_delays);
        animSet->addAnimation("swingO2", 3, this->swingO2_frames, this->swingO2_originXs, this->swingO2_originYs, this->swingO2_delays);
        animSet->addAnimation("swingO3", 3, this->swingO3_frames, this->swingO3_originXs, this->swingO3_originYs, this->swingO3_delays);
        animSet->addAnimation("swingOF", 4, this->swingOF_frames, this->swingOF_originXs, this->swingOF_originYs, this->swingOF_delays);
        animSet->addAnimation("stabO1", 2, this->stabO1_frames, this->stabO1_originXs, this->stabO1_originYs, this->stabO1_delays);
        animSet->addAnimation("stabO2", 2, this->stabO2_frames, this->stabO2_originXs, this->stabO2_originYs, this->stabO2_delays);
        animSet->addAnimation("stabOF", 3, this->stabOF_frames, this->stabOF_originXs, this->stabOF_originYs, this->stabOF_delays);
        animSet->addAnimation("proneStab", 2, this->proneStab_frames, this->proneStab_originXs, this->proneStab_originYs, this->proneStab_delays);
        animSet->addAnimation("prone", 1, this->prone_frames, this->prone_originXs, this->prone_originYs, this->prone_delays);
        animSet->addAnimation("heal", 3, this->heal_frames, this->heal_originXs, this->heal_originYs, this->heal_delays);
        animSet->addAnimation("fly", 2, this->fly_frames, this->fly_originXs, this->fly_originYs, this->fly_delays);
        animSet->addAnimation("jump", 1, this->jump_frames, this->jump_originXs, this->jump_originYs, this->jump_delays);
        animSet->addAnimation("sit", 1, this->sit_frames, this->sit_originXs, this->sit_originYs, this->sit_delays);
        animSet->addAnimation("ladder", 2, this->ladder_frames, this->ladder_originXs, this->ladder_originYs, this->ladder_delays);
        animSet->addAnimation("rope", 2, this->rope_frames, this->rope_originXs, this->rope_originYs, this->rope_delays);

        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Assets loaded in!");
    }

    void TestStage::onUnload() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Unloading");

        // release all our assets we loaded in
        CSEA::Assets::AssetManager::releaseAsset("assets/test1/fragmentShader.fs");
        CSEA::Assets::AssetManager::unloadAsset("assets/test1/fragmentShader.fs");

        CSEA::Assets::AssetManager::releaseAsset("assets/test1/vertexShader.vs");
        CSEA::Assets::AssetManager::unloadAsset("assets/test1/vertexShader.vs");

        CSEA::Assets::AssetManager::releaseAsset("assets/test1/toruSheet.png");
        CSEA::Assets::AssetManager::unloadAsset("assets/test1/toruSheet.png");

        CSEA::Assets::AssetManager::releaseAsset("assets/test1/toruAnimSet.xml");
        CSEA::Assets::AssetManager::unloadAsset("assets/test1/toruAnimSet.xml");
    }

    void TestStage::onTransitionInto() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Transitioning in.");
        // This is when our stage first becomes the active stage;
        // We need to add our scenes and viewports into the renderer

        // the order of scenes added does not matter, they'll be updated in an arbitrary order anyhow
        CSEA::Render::Renderer::addScene(this->uiScene);
        CSEA::Render::Renderer::addScene(this->gameScene);

        // Viewports however, are rendered in order of addition - so first game, then UI
        CSEA::Render::Renderer::addViewport(this->gameViewport);
        CSEA::Render::Renderer::addViewport(this->uiViewport);

        // Add our objects to ourselves (addObject is implemented in CSEA::Core::Stage, which this class extends)
        this->addObject(this->testObject1);
        this->addObject(this->testObject2);
        this->addObject(this->testPlayer);

        // This class implements an InputListener, which allows it to receive inputs after registration
        // - InputListeners are registered under input groups (in this case, TEST_STAGE)
        // - Listeners of the same group are guaranteed to be executed in order of addition
        // - Listeners of different groups are guaranteed to be executed, but have no order guarantee
        CSEA::Input::InputManager::registerInputListener(this, "TEST_STAGE");
    }

    void TestStage::onTransitionOutOf() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Transitioning Out.");

        // unregister us
        CSEA::Input::InputManager::unregisterInputListener(this, "TEST_STAGE");

        // note that order of removal isn't too important
        CSEA::Render::Renderer::removeScene(this->uiScene);
        CSEA::Render::Renderer::removeScene(this->gameScene);

        CSEA::Render::Renderer::removeViewport(this->gameViewport);
        CSEA::Render::Renderer::removeViewport(this->uiViewport);

        // take out our objects
        this->removeObject(this->testObject1);
        this->removeObject(this->testObject2);
        this->removeObject(this->testPlayer);

        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Scene has been removed.");
    }

    void TestStage::onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        // Pretty self explanatory function - Escape = exit, Tab = toggle visibility, Arrows = Move Game Cam
        if (key == CSELL::Core::InputEnum::K_ESCAPE && action == CSELL::Core::InputEnum::ACTION_PRESS) {
            CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "onEscapeKey");
            CSEA::Core::Engine::exit();
        }

        if (key == CSELL::Core::InputEnum::K_TAB) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                this->gameViewport->setVisible(false);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                this->gameViewport->setVisible(true);
            }
        }

        CSELL::Math::Vector3f dir, camPos;
        this->gameCam->getPosition(camPos); // stores the cameras current position in camPos

        if (key == CSELL::Core::InputEnum::K_UP) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(0.0f, 25.0f, 0.0f);
            }
        }
        if (key == CSELL::Core::InputEnum::K_DOWN) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(0.0f, -25.0f, 0.0f);
            }
        }
        if (key == CSELL::Core::InputEnum::K_LEFT) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(-25.0f, 0.0f, 0.0f);
            }
        }
        if (key == CSELL::Core::InputEnum::K_RIGHT) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(25.0f, 0.0f, 0.0f);
            }
        }

        // only move if this event actually triggered camera motion
        if (dir.magnitudeSquared()!= 0.0f) {
            this->gameCam->setPosition(dir+camPos);
        }
    }

    void TestStage::onWindowCloseInput() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "onWindowClose");
        // Also pretty self explanatory - kill the engine if we clicked the X
        CSEA::Core::Engine::exit();
    };
}}
