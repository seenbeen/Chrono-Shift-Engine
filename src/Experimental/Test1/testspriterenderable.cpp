#include <CSE/Experimental/Test1/testspriterenderable.hpp>
#include <string>

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

#include <CSE/CSEA/asset/spriteanimationset.hpp>

namespace Experimental { namespace Test1 {
    TestSpriteRenderable::TestSpriteRenderable(const std::string &anim) {
        this->animSet = NULL;
        this->cutOuts = NULL;
        this->shaderProgram = NULL;
        this->spriteSheet = NULL;
        this->anim = anim;
    }

    TestSpriteRenderable::~TestSpriteRenderable() {}

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

        this->animSet = CSEA::Assets::AssetManager::getSpriteAnimationSet("assets/test1/toruAnimSet.xml");
        this->setup(this->animSet, this->spriteSheet, this->cutOuts, this->shaderProgram);
        this->setCurrentAnimation(this->anim);
        return true;
    }

    bool TestSpriteRenderable::onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        CSU::Logger::log(CSU::Logger::DEBUG, CSU::Logger::EXPERIMENTAL, "Test1 - TestSpriteRenderable", "On Unload.");

        CSEA::Assets::AssetManager::releaseAsset("assets/test1/toruAnimSet.xml");
        cacheManager->releaseMesh("TestSpriteRenderable->CutOuts");
        cacheManager->releaseTexture("TestSpriteRenderable->SpriteSheet");
        cacheManager->releaseShaderProgram("TestSpriteRenderable->ShaderProgram");

        this->animSet = NULL;
        this->cutOuts = NULL;
        this->spriteSheet = NULL;
        this->shaderProgram = NULL;

        return true;
    }

}}
