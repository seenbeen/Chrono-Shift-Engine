#ifndef EXPERIMENTAL_TEST1_TESTRENDERABLE_HPP
#define EXPERIMENTAL_TEST1_TESTRENDERABLE_HPP

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSEA/render/cachemanager.hpp>
#include <CSE/CSEA/render/renderable.hpp>
#include <CSE/CSEA/render/camera.hpp>

#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/shader.hpp>
#include <CSE/CSELL/render/shaderprogram.hpp>

namespace Experimental { namespace Test1 {
    class TestRenderable: public CSEA::Render::Renderable {
        CSELL::Render::Mesh *mesh;
        CSELL::Render::Texture *tex1, *tex2;
        CSELL::Render::ShaderProgram *shaderProgram;
        const unsigned int nVertices = 36;
        const unsigned int nVertexElements = 36;

        CSELL::Render::Mesh::Vertex meshVertices[36] = {
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 0.0f, 0.0f,}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 1.0f, 0.0f,}},
            {{0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 1.0f, 1.0f,}},
            {{0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 1.0f, 1.0f,}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 0.0f, 1.0f,}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, { 0.0f, 0.0f,}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f,}},
            {{0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 0.0f,}},
            {{0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 1.0f,}},
            {{0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 1.0f,}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 1.0f,}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f,}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f,}},
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f,}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, { 1.0f, 1.0f,}},
            {{0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, { 0.0f, 0.0f,}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f,}},
            {{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 1.0f,}},
            {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f,}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f,}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f}}
        };

        unsigned int meshVertexElements[36] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
            12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
            24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
        };

    protected:
        bool onLoad(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager);
        bool onUnload(CSELL::Render::Renderer *renderer, CSEA::Render::CacheManager *cacheManager);
        void onUpdate(double deltaTime);
        void onRender(CSEA::Render::Camera *camera);

    public:
        TestRenderable();
        ~TestRenderable();
    };
}}
#endif

