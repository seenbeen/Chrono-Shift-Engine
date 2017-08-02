#include <CSE/Experimental/Test1/teststage.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSEA/asset/assetmanager.hpp>

#include <CSE/CSEA/core/stage.hpp>

#include <CSE/CSEA/render/renderer.hpp>
#include <CSE/CSEA/render/viewport.hpp>
#include <CSE/CSEA/render/scene.hpp>
#include <CSE/CSEA/render/orthographiccamera.hpp>

namespace Experimental { namespace Test1 {
    TestStage::TestStage() {
        this->viewport = new CSEA::Render::Viewport(0,0,800,600); // hoping this works...
        this->scene = new CSEA::Render::Scene();

        float aspect = 800.0f / 600.0f;

        this->camera = new CSEA::Render::OrthographicCamera(-5.0f*aspect, 5.0f*aspect, -5.0f, 5.0f, 0.1f, 100.0f);

        this->viewport->bindScene(this->scene);
        this->viewport->bindCamera(this->camera);
    }

    TestStage::~TestStage() {
        delete this->scene;
        delete this->camera;
        delete this->viewport;
    }

    void TestStage::onLoad() {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Experimental/Test1 - TestStage", "Loading test stage");
        CSEA::Assets::AssetManager::loadFile("assets/shaders/fragmentShader1.fs");
        CSEA::Assets::AssetManager::loadFile("assets/shaders/vertexShader1.vs");
        CSEA::Assets::AssetManager::loadImage("assets/textures/texturesLesson/container.jpg");
        CSEA::Assets::AssetManager::loadImage("assets/textures/texturesLesson/awesomeface.png");
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::CSEA, "Experimental/Test1 - TestStage", "Assets loaded in!");
    }

    void TestStage::onUnload() {
        CSEA::Assets::AssetManager::unloadAsset("assets/shaders/fragmentShader1.fs");
        CSEA::Assets::AssetManager::unloadAsset("assets/shaders/vertexShader1.vs");
        CSEA::Assets::AssetManager::unloadAsset("assets/textures/texturesLesson/container.jpg");
        CSEA::Assets::AssetManager::unloadAsset("assets/textures/texturesLesson/awesomeface.png");
    }

    void TestStage::onTransitionInto() {
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
        CSEA::Render::Renderer::removeScene(this->scene);
        CSEA::Render::Renderer::removeViewport(this->viewport);
    }
}}
