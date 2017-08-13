#include <CSE/Experimental/FontTest/fontrenderable.hpp>

#include <CSE/CSEA/font/fontrasterizer.hpp>
#include <CSE/CSEA/font/rasterizedfont.hpp>
#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>

#include <CSE/CSELL/math/vector3f.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSEA/render/camera.hpp>
namespace Experimental { namespace FontTest {
    bool FontRenderable::onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        this->rFont = CSEA::Font::FontRasterizer::getRasterizedFont("TEST_STAGE_ARIAL1");
        CSELL::Render::Mesh::Vertex vertices[4] = {
            {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{0.0f, rFont->getTextureHeight(), 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f,1.0f}},
            {{rFont->getTextureWidth(), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,0.0f}},
            {{rFont->getTextureWidth(), rFont->getTextureHeight(), 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,1.0f}}
        };
        unsigned int elements[6] = { 0, 3, 1, 0, 2, 3 };
        this->mesh = renderer->newMesh(4, vertices, 6, elements);
        this->texture = renderer->newTexture(this->rFont->getTextureWidth(), this->rFont->getTextureHeight(),
                                             this->rFont->getTextureImage());
        this->shaderProgram = cacheManager->retrieveShaderProgram("TestSpriteRenderable->ShaderProgram");
        return true;
    }

    bool FontRenderable::onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager) {
        return true;
    }

    void FontRenderable::onUpdate(double deltaTime) {

    }

    void FontRenderable::onRender(CSEA::Render::Camera *camera) {
        glm::mat4 tempMat;

        this->shaderProgram->useShaderProgram();

        CSELL::Math::Transform &xform = *this->xform;

        tempMat = glm::translate(tempMat, glm::vec3(xform.position.x, xform.position.y, xform.position.z));

        tempMat = glm::scale(tempMat, glm::vec3(xform.scale.x, xform.scale.y, 1.0f));

        tempMat = glm::rotate(tempMat, glm::radians(xform.orientation.z), glm::vec3(0.0f,0.0f,1.0f));

        this->shaderProgram->setMat4f("model", glm::value_ptr(tempMat));

        camera->getViewMatrix(tempMat);

        this->shaderProgram->setMat4f("view", glm::value_ptr(tempMat));

        camera->getProjMatrix(tempMat);

        this->shaderProgram->setMat4f("projection",glm::value_ptr(tempMat));

        this->shaderProgram->setInt("spriteSheet", 0);
        this->texture->useActiveTexture(0);
        this->mesh->useMesh();

        this->mesh->renderMesh(0,6);
    }

    FontRenderable::FontRenderable() {

    }

    FontRenderable::~FontRenderable() {

    }
}}

