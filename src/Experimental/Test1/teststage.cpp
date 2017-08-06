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

#include <CSE/Experimental/Test1/testgameobject.hpp>

namespace Experimental { namespace Test1 {
    TestStage::TestStage() {
        this->viewport = new CSEA::Render::Viewport(0,0,800,600); // hoping this works...
        this->scene = new CSEA::Render::Scene();

        float aspect = 800.0f / 600.0f;

        this->camera = new CSEA::Render::OrthographicCamera(-1.0f*aspect, 1.0f*aspect, -1.0f, 1.0f, 0.1f, 100.0f);
        this->camera->setPosition(CSELL::Math::Vector3f(0.0f,0.0f,4.0f));
        this->viewport->bindScene(this->scene);
        this->viewport->bindCamera(this->camera);

        // gulp...
        CSELL::Math::Vector3f pos = CSELL::Math::Vector3f(-0.5f, 0.5f, -2.0f);
        this->testObject1 = new Experimental::Test1::TestGameObject(this->scene, pos);
        pos += CSELL::Math::Vector3f(0.5f, -0.5f, 2.0f);
        this->testObject2 = new Experimental::Test1::TestGameObject(this->scene, pos);
        pos -= CSELL::Math::Vector3f(-0.5f, 0.5f, 1.0f);
        this->testObject3 = new Experimental::Test1::TestGameObject(this->scene, pos);

        this->addObject(this->testObject1);
        this->addObject(this->testObject2);
        this->addObject(this->testObject3);
    }

    TestStage::~TestStage() {
        this->removeObject(this->testObject1);
        this->removeObject(this->testObject2);
        this->removeObject(this->testObject3);
        delete this->testObject1;
        delete this->testObject2;
        delete this->testObject3;
        delete this->scene;
        delete this->camera;
        delete this->viewport;
    }

    void TestStage::onLoad() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Loading");
        CSEA::Assets::AssetManager::loadFile("assets/shaders/fragmentShader1.fs");
        CSEA::Assets::AssetManager::loadFile("assets/shaders/vertexShader1.vs");
        CSEA::Assets::AssetManager::loadImage("assets/textures/texturesLesson/container.jpg");
        CSEA::Assets::AssetManager::loadImage("assets/textures/texturesLesson/awesomeface.png");
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Assets loaded in!");
        CSEA::Input::InputManager::registerInputListener(this);
    }

    void TestStage::onUnload() {
        CSEA::Input::InputManager::unregisterInputListener(this);
        CSEA::Assets::AssetManager::releaseAsset("assets/shaders/fragmentShader1.fs");
        CSEA::Assets::AssetManager::unloadAsset("assets/shaders/fragmentShader1.fs");

        CSEA::Assets::AssetManager::releaseAsset("assets/shaders/vertexShader1.vs");
        CSEA::Assets::AssetManager::unloadAsset("assets/shaders/vertexShader1.vs");

        CSEA::Assets::AssetManager::releaseAsset("assets/textures/texturesLesson/container.jpg");
        CSEA::Assets::AssetManager::unloadAsset("assets/textures/texturesLesson/container.jpg");

        CSEA::Assets::AssetManager::releaseAsset("assets/textures/texturesLesson/awesomeface.png");
        CSEA::Assets::AssetManager::unloadAsset("assets/textures/texturesLesson/awesomeface.png");
    }

    void TestStage::onTransitionInto() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Transitioning in.");
        CSEA::Render::Renderer::addScene(this->scene);
        CSEA::Render::Renderer::addViewport(this->viewport);
        /*
        glm::vec3 cubePositions[] = {
          glm::vec3( 0.0f,  0.0f,  0.0f),
          glm::vec3( 2.0f,  5.0f, -15.0f),
          glm::vec3(-1.5f, -2.2f, -2.5f),
          glm::vec3(-3.8f, -2.0f, -12.3f),
          glm::vec3( 2.4f, -0.4f, -3.5f),
          glm::vec3(-1.7f,  3.0f, -7.5f),
          glm::vec3( 1.3f, -2.0f, -2.5f),
          glm::vec3( 1.5f,  2.0f, -2.5f),
          glm::vec3( 1.5f,  0.2f, -1.5f),
          glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        while(running) {
            // Draw stuff
            for(unsigned int i = 0; i < 10; i++) {
                model = glm::translate(identity, cubePositions[i]);
                float angle = glm::radians(20.0f * i) + CSELL::Core::Time::getTime() * glm::radians(60.0f);
                model = glm::rotate(model, (i%2 ? 1 : -1)*angle, glm::vec3(1.0f, 0.3f, 0.5f));
                shaderProgram->setMat4f("model", glm::value_ptr(model));
                mesh->renderMesh();
            }
        }*/
        // initiate the cube creation of test game objects
    }

    void TestStage::onTransitionOutOf() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "Transitioning Out.");
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
                dir += CSELL::Math::Vector3f(0.0f, 0.2f, 0.0f);
            }
        }
        if (key == CSELL::Core::InputEnum::K_DOWN) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(0.0f, -0.2f, 0.0f);
            }
        }
        if (key == CSELL::Core::InputEnum::K_LEFT) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(-0.2f, 0.0f, 0.0f);
            }
        }
        if (key == CSELL::Core::InputEnum::K_RIGHT) {
            if (action == CSELL::Core::InputEnum::ACTION_PRESS) {
                dir += CSELL::Math::Vector3f(0.2f, 0.0f, 0.0f);
            }
        }
        if (dir.magnitudeSquared()!= 0.0f) {
            this->camera->setPosition(dir+camPos);
        }
    }

    void TestStage::onMousePosInput(double xpos, double ypos, double xrel, double yrel) {}
    void TestStage::onMouseButtonInput(CSELL::Core::InputEnum::MouseButton button, CSELL::Core::InputEnum::InputAction action) {}
    void TestStage::onMouseScrollInput(double xoffset, double yoffset) {}
    void TestStage::onMouseEnterLeaveInput(bool entered) {}
    void TestStage::onWindowResizeInput(unsigned int width, unsigned int height) {
        this->viewport->setDimensions(width, height);
    }
    void TestStage::onWindowCloseInput() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestStage", "onWindowClose");
        CSEA::Core::Engine::exit();
    };
}}
