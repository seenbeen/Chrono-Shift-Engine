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

        unsigned int n = this->rFont->getNGlyphs();
        unsigned int nVerts = n * 4; // 4 vertices per glyph
        unsigned int nElements = n * 6; // 6 vertices per glyph = 2 tris

        CSELL::Render::Mesh::Vertex vertices[nVerts];
        unsigned int elements[nElements];

        unsigned int *gX = this->rFont->getGlyphXs();
        unsigned int *gY = this->rFont->getGlyphYs();
        unsigned int *gW = this->rFont->getGlyphWidths();
        unsigned int *gH = this->rFont->getGlyphHeights();

        unsigned int texW = this->rFont->getTextureWidth();
        unsigned int texH = this->rFont->getTextureHeight();

        float vertexOrder[6] = { 0.0f, 2.0f, 1.0f, 0.0f, 3.0f, 2.0f };

        for (unsigned int i = 0; i < n; i++) {
            vertices[i * 4] = {{0.0f, 0.0f, 0.0f},
                               {0.0f, 0.0f, 1.0f},
                               {(float)gX[i] / texW, (float)gY[i] / texH}};

            vertices[i * 4 + 1] = {{0.0f, (float)gH[i], 0.0f},
                                   {0.0f, 0.0f, 1.0f},
                                   {(float)gX[i] / texW, (float)(gY[i] + gH[i]) / texH}};

            vertices[i * 4 + 2] = {{(float)gW[i] , (float)gH[i], 0.0f},
                                   {0.0f, 0.0f, 1.0f},
                                   {(float)(gX[i] + gW[i]) / texW, (float)(gY[i] + gH[i]) / texH}};

            vertices[i * 4 + 3] = {{(float)gW[i], 0.0f, 0.0f},
                                   {0.0f, 0.0f, 1.0f},
                                   {(float)(gX[i] + gW[i]) / texW, (float)gY[i] / texH}};

            for (unsigned int j = 0; j < 6; j++) {
                elements[i*6 + j] = (float) i*4 + vertexOrder[j];
            }
        }

        /*
        CSELL::Render::Mesh::Vertex vertices[4] = {
            {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{0.0f, rFont->getTextureHeight(), 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f,1.0f}},
            {{rFont->getTextureWidth(), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,0.0f}},
            {{rFont->getTextureWidth(), rFont->getTextureHeight(), 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,1.0f}}
        };
        unsigned int elements[6] = { 0, 3, 1, 0, 2, 3 };*/
        this->mesh = renderer->newMesh(nVerts, vertices, nElements, elements);
        this->texture = renderer->newTexture(texW, texH, this->rFont->getTextureImage());
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

        unsigned int offx, offy, advance, idx;
        this->rFont->queryGlyphData('S',offx,offy,advance,idx);
        this->mesh->renderMesh(idx*6,(idx+1)*6);
    }

    FontRenderable::FontRenderable() {

    }

    FontRenderable::~FontRenderable() {

    }
}}

