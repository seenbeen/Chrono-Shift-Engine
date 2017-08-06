#include <CSE/Experimental/Test1/testrenderable.hpp>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/asset/text.hpp>
#include <CSE/CSELL/asset/image.hpp>

#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/shader.hpp>
#include <CSE/CSELL/render/shaderprogram.hpp>

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSEA/asset/assetmanager.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSEA/render/camera.hpp>

namespace Experimental { namespace Test1 {
    bool TestRenderable::onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestRenderable", "On Load.");
        this->shaderProgram = cacheManager->retrieveShaderProgram("TestRenderable->ShaderProgram");
        if (this->shaderProgram == NULL) {
            CSELL::Assets::TextAsset *fsContent, *vsContent;
            CSELL::Render::Shader *fragmentShader, *vertexShader;

            fsContent = CSEA::Assets::AssetManager::getFile("assets/shaders/fragmentShader1.fs");

            fragmentShader = renderer->newShader(fsContent->getContents()->c_str(), CSELL::Render::Shader::FRAGMENT_SHADER);

            CSEA::Assets::AssetManager::releaseAsset("assets/shaders/fragmentShader1.fs");

            vsContent = CSEA::Assets::AssetManager::getFile("assets/shaders/vertexShader1.vs");

            vertexShader = renderer->newShader(vsContent->getContents()->c_str(), CSELL::Render::Shader::VERTEX_SHADER);

            CSEA::Assets::AssetManager::releaseAsset("assets/shaders/vertexShader1.vs");

            this->shaderProgram = renderer->newShaderProgram();
            this->shaderProgram->attachShader(vertexShader);
            this->shaderProgram->attachShader(fragmentShader);
            this->shaderProgram->linkShaderProgram();

            renderer->deleteShader(fragmentShader);
            fragmentShader = NULL;

            renderer->deleteShader(vertexShader);
            vertexShader = NULL;

            // cache it
            cacheManager->cacheShaderProgram("TestRenderable->ShaderProgram", this->shaderProgram);
        }

        this->tex1 = cacheManager->retrieveTexture("TestRenderable->Tex1");
        if (this->tex1 == NULL) {
            CSELL::Assets::ImageAsset *img;

            img = CSEA::Assets::AssetManager::getImage("assets/textures/texturesLesson/container.jpg");
            this->tex1 = renderer->newTexture(img->width(), img->height(), img->data());
            cacheManager->cacheTexture("TestRenderable->Tex1", this->tex1);
            CSEA::Assets::AssetManager::releaseAsset("assets/textures/texturesLesson/container.jpg");
        }

        this->tex2 = cacheManager->retrieveTexture("TestRenderable->Tex2");
        if (this->tex2 == NULL) {
            CSELL::Assets::ImageAsset *img;

            img = CSEA::Assets::AssetManager::getImage("assets/textures/texturesLesson/awesomeface.png");
            this->tex2 = renderer->newTexture(img->width(), img->height(), img->data());
            cacheManager->cacheTexture("TestRenderable->Tex2", this->tex2);
            CSEA::Assets::AssetManager::releaseAsset("assets/textures/texturesLesson/awesomeface.png");
        }

        this->mesh = cacheManager->retrieveMesh("TestRenderable->Mesh");
        if (this->mesh == NULL) {
            this->mesh = renderer->newMesh(this->nVertices, this->meshVertices,
                                           this->nVertexElements, this->meshVertexElements);
            cacheManager->cacheMesh("TestRenderable->Mesh", this->mesh);
        }
        return true;
    }

    bool TestRenderable::onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestRenderable", "On Unload.");

        cacheManager->releaseShaderProgram("TestRenderable->ShaderProgram");
        cacheManager->releaseTexture("TestRenderable->Tex1");
        cacheManager->releaseTexture("TestRenderable->Tex2");
        cacheManager->releaseMesh("TestRenderable->Mesh");

        return true;
    }

    void TestRenderable::onUpdate(double deltaTime) {
        // use this area to make renderables that animate or something...
    }

    void TestRenderable::onRender(CSEA::Render::Camera *camera) {
        glm::mat4 tempMat, identity;
        this->shaderProgram->useShaderProgram();
        tempMat = glm::rotate(tempMat, 3.14f/6.0f, glm::vec3(0.0f,0.0f,1.0f));
        //tempMat = glm::translate(tempMat, glm::vec3(0.0f, 0.0f, -4.0f));
        // set the model matrix; guess our model matrix is default
        this->shaderProgram->setMat4f("model", glm::value_ptr(tempMat));

        camera->getViewMatrix(tempMat);
        this->shaderProgram->setMat4f("view", glm::value_ptr(tempMat));

        camera->getProjMatrix(tempMat);
        this->shaderProgram->setMat4f("projection", glm::value_ptr(tempMat));

        this->shaderProgram->setInt("tex1", 0);
        this->shaderProgram->setInt("tex2", 1);
        this->tex1->useActiveTexture(0);
        this->tex2->useActiveTexture(1);

        this->mesh->useMesh();
        this->mesh->renderMesh();
    }

    TestRenderable::TestRenderable() {
        this->mesh = NULL;
        this->tex1 = NULL;
        this->tex2 = NULL;
        this->shaderProgram = NULL;
    }
    TestRenderable::~TestRenderable() {}
}}
