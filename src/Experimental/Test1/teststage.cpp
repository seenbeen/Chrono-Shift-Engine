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
#include <CSE/CSEA/render/orthographiccamera.hpp>

#include <CSE/CSEA/asset/spriteanimationset.hpp>

#include <CSE/Experimental/Test1/testgameobject.hpp>

namespace Experimental { namespace Test1 {
    TestStage::TestStage() {
        this->viewport = new CSEA::Render::Viewport(0,0,800,600); // hoping this works...
        this->scene = new CSEA::Render::Scene();

        this->camera = new CSEA::Render::OrthographicCamera(-400, 400, -300, 300, 0.1f, 100.0f);
        this->camera->setPosition(CSELL::Math::Vector3f(0.0f,0.0f,4.0f));
        this->viewport->bindScene(this->scene);
        this->viewport->bindCamera(this->camera);

        // gulp...
        CSELL::Math::Transform xform;
        xform.position = CSELL::Math::Vector3f(-200.0f, 150.0f, -2.0f);
        this->testObject1 = new Experimental::Test1::TestGameObject(this->scene, "walk1");
        xform.position += CSELL::Math::Vector3f(200.0f, -150.0f, 2.0f);
        this->testObject2 = new Experimental::Test1::TestGameObject(this->scene, "stand1");
        xform.position -= CSELL::Math::Vector3f(-200.0f, 150.0f, 1.0f);
        this->testObject3 = new Experimental::Test1::TestGameObject(this->scene, "swingOF");
    }

    TestStage::~TestStage() {
        delete this->testObject1;
        delete this->testObject2;
        delete this->testObject3;
        delete this->scene;
        delete this->camera;
        delete this->viewport;
    }

    void TestStage::onLoad() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Loading");

        // sprite
        CSEA::Assets::AssetManager::loadFile("assets/test1/fragmentShader.fs");
        CSEA::Assets::AssetManager::loadFile("assets/test1/vertexShader.vs");
        CSEA::Assets::AssetManager::loadImage("assets/test1/toruSheet.png");

        CSEA::Assets::SpriteAnimationSet *animSet;
        animSet = CSEA::Assets::AssetManager::loadSpriteAnimationSet("assets/test1/toruAnimSet.xml");

        // should be loaded in by a loader in the future, implemented in AssetManager (above call)
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

        // sprite
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
        CSEA::Render::Renderer::addScene(this->scene);
        CSEA::Render::Renderer::addViewport(this->viewport);

        this->addObject(this->testObject2);
        this->addObject(this->testObject3);
        this->addObject(this->testObject1);
        CSEA::Input::InputManager::registerInputListener(this, "TEST_STAGE");
    }

    void TestStage::onTransitionOutOf() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Transitioning Out.");
        CSEA::Input::InputManager::unregisterInputListener(this, "TEST_STAGE");
        this->removeObject(this->testObject1);
        this->removeObject(this->testObject2);
        this->removeObject(this->testObject3);

        CSEA::Render::Renderer::removeViewport(this->viewport);
        CSEA::Render::Renderer::removeScene(this->scene);
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Scene has been removed.");
    }

    void TestStage::onKeyInput(CSELL::Core::InputEnum::KeyboardKey key, CSELL::Core::InputEnum::InputAction action) {
        if (key == CSELL::Core::InputEnum::K_ESCAPE && action == CSELL::Core::InputEnum::ACTION_PRESS) {
            CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "onEscapeKey");
            CSEA::Core::Engine::exit();
        }
        if (key == CSELL::Core::InputEnum::K_TAB) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                this->viewport->setVisible(false);
                CSEA::Render::Renderer::removeScene(this->scene);
            } else if (action == CSELL::Core::InputEnum::ACTION_RELEASE) {
                this->viewport->setVisible(true);
                CSEA::Render::Renderer::addScene(this->scene);
            }
        }
        CSELL::Math::Vector3f dir, camPos;
        this->camera->getPosition(camPos);
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
        if (dir.magnitudeSquared()!= 0.0f) {
            this->camera->setPosition(dir+camPos);
        }
    }

    void TestStage::onWindowResizeInput(unsigned int width, unsigned int height) {
        this->viewport->setDimensions(width, height);
        float w = width, h = height; // casting so we don't get arbitrarily high numbers for negatives
        this->camera->resizeFrustum(-w / 2.0f, w / 2.0f, -h / 2.0f, h / 2.0f, 0.1f, 100.0f);
    }

    void TestStage::onWindowCloseInput() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "onWindowClose");
        CSEA::Core::Engine::exit();
    };
}}
