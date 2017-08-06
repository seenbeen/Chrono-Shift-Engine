#include <CSE/Experimental/Test1/testspriterenderable.hpp>

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

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

#include <iostream>

namespace Experimental { namespace Test1 {
    TestSpriteRenderable::TestSpriteRenderable(const CSELL::Math::Vector3f &position) {
        this->xform.position = position;
        this->addAnimation("walk1", 4, this->walk1_frames, this->walk1_originXs, this->walk1_originYs, this->walk1_delays);
        this->addAnimation("stand1", 5, this->stand1_frames, this->stand1_originXs, this->stand1_originYs, this->stand1_delays);
        this->addAnimation("alert", 5, this->alert_frames, this->alert_originXs, this->alert_originYs, this->alert_delays);
        this->addAnimation("swingO1", 3, this->swingO1_frames, this->swingO1_originXs, this->swingO1_originYs, this->swingO1_delays);
        this->addAnimation("swingO2", 3, this->swingO2_frames, this->swingO2_originXs, this->swingO2_originYs, this->swingO2_delays);
        this->addAnimation("swingO3", 3, this->swingO3_frames, this->swingO3_originXs, this->swingO3_originYs, this->swingO3_delays);
        this->addAnimation("swingOF", 4, this->swingOF_frames, this->swingOF_originXs, this->swingOF_originYs, this->swingOF_delays);
        this->addAnimation("stabO1", 2, this->stabO1_frames, this->stabO1_originXs, this->stabO1_originYs, this->stabO1_delays);
        this->addAnimation("stabO2", 2, this->stabO2_frames, this->stabO2_originXs, this->stabO2_originYs, this->stabO2_delays);
        this->addAnimation("stabOF", 3, this->stabOF_frames, this->stabOF_originXs, this->stabOF_originYs, this->stabOF_delays);
        this->addAnimation("proneStab", 2, this->proneStab_frames, this->proneStab_originXs, this->proneStab_originYs, this->proneStab_delays);
        this->addAnimation("prone", 1, this->prone_frames, this->prone_originXs, this->prone_originYs, this->prone_delays);
        this->addAnimation("heal", 3, this->heal_frames, this->heal_originXs, this->heal_originYs, this->heal_delays);
        this->addAnimation("fly", 2, this->fly_frames, this->fly_originXs, this->fly_originYs, this->fly_delays);
        this->addAnimation("jump", 1, this->jump_frames, this->jump_originXs, this->jump_originYs, this->jump_delays);
        this->addAnimation("sit", 1, this->sit_frames, this->sit_originXs, this->sit_originYs, this->sit_delays);
        this->addAnimation("ladder", 2, this->ladder_frames, this->ladder_originXs, this->ladder_originYs, this->ladder_delays);
        this->addAnimation("rope", 2, this->rope_frames, this->rope_originXs, this->rope_originYs, this->rope_delays);
        this->setCurrentAnimation("alert");
    }

    TestSpriteRenderable::~TestSpriteRenderable() {
        this->deleteAnimation("walk1");
        this->deleteAnimation("stand1");
        this->deleteAnimation("alert");
        this->deleteAnimation("swingO1");
        this->deleteAnimation("swingO2");
        this->deleteAnimation("swingO3");
        this->deleteAnimation("swingOF");
        this->deleteAnimation("stabO1");
        this->deleteAnimation("stabO2");
        this->deleteAnimation("stabOF");
        this->deleteAnimation("proneStab");
        this->deleteAnimation("prone");
        this->deleteAnimation("heal");
        this->deleteAnimation("fly");
        this->deleteAnimation("jump");
        this->deleteAnimation("sit");
        this->deleteAnimation("ladder");
        this->deleteAnimation("rope");
    }

    bool TestSpriteRenderable::onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestSpriteRenderable", "On Load.");
        this->shaderProgram = cacheManager->retrieveShaderProgram("TestSpriteRenderable->ShaderProgram");
        if (this->shaderProgram == NULL) {
            CSELL::Assets::TextAsset *fsContent, *vsContent;
            CSELL::Render::Shader *fragmentShader, *vertexShader;

            fsContent = CSEA::Assets::AssetManager::getFile("assets/test1/fragmentShader.fs");

            fragmentShader = renderer->newShader(fsContent->getContents()->c_str(), CSELL::Render::Shader::FRAGMENT_SHADER);

            CSEA::Assets::AssetManager::releaseAsset("assets/test1/fragmentShader.fs");

            vsContent = CSEA::Assets::AssetManager::getFile("assets/test1/vertexShader.vs");

            vertexShader = renderer->newShader(vsContent->getContents()->c_str(), CSELL::Render::Shader::VERTEX_SHADER);

            CSEA::Assets::AssetManager::releaseAsset("assets/test1/vertexShader.vs");

            this->shaderProgram = renderer->newShaderProgram();
            this->shaderProgram->attachShader(vertexShader);
            this->shaderProgram->attachShader(fragmentShader);
            this->shaderProgram->linkShaderProgram();

            renderer->deleteShader(fragmentShader);
            fragmentShader = NULL;

            renderer->deleteShader(vertexShader);
            vertexShader = NULL;

            // cache it
            cacheManager->cacheShaderProgram("TestSpriteRenderable->ShaderProgram", this->shaderProgram);
        }

        this->spriteSheet = cacheManager->retrieveTexture("TestSpriteRenderable->SpriteSheet");
        if (this->spriteSheet == NULL) {
            CSELL::Assets::ImageAsset *img;

            img = CSEA::Assets::AssetManager::getImage("assets/test1/toruSheet.png");
            this->spriteSheet = renderer->newTexture(img->width(), img->height(), img->data());
            cacheManager->cacheTexture("TestSpriteRenderable->SpriteSheet", this->spriteSheet);
            CSEA::Assets::AssetManager::releaseAsset("assets/test1/toruSheet.png");
        }

        this->cutOuts = cacheManager->retrieveMesh("TestSpriteRenderable->CutOuts");
        if (this->cutOuts == NULL) {
            this->cutOuts = renderer->newMesh(this->nVertices, this->vertices,
                                           this->nVertexElements, this->vertexElements);
            cacheManager->cacheMesh("TestSpriteRenderable->CutOuts", this->cutOuts);
        }

        this->setup(this->spriteSheet, this->cutOuts, this->shaderProgram);

        return true;
    }

    bool TestSpriteRenderable::onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestSpriteRenderable", "On Unload.");

        cacheManager->releaseTexture("TestSpriteRenderable->SpriteSheet");
        cacheManager->releaseMesh("TestSpriteRenderable->CutOuts");
        cacheManager->releaseShaderProgram("TestSpriteRenderable->ShaderProgram");

        return true;
    }

}}
