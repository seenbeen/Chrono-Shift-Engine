#ifndef CSELL_RENDERER_ENGINE_HPP
#define CSELL_RENDERER_ENGINE_HPP

#include <string>

#include <CSE/CSELL/renderer/mesh.hpp>
#include <CSE/CSELL/renderer/shaders.hpp>
#include <CSE/CSELL/renderer/texture.hpp>
#include <CSE/CSELL/renderer/camera.hpp>

namespace CSELL { namespace Renderer {
    struct RenderEngineSettings {
        unsigned int defaultWidth, defaultHeight;
        bool resizeable;
        std::string windowName;
    };

    class RenderEngine {
        static bool isInitialized;
        bool ensureIsInitialized();
    public:
        static void init(const RenderEngineSettings &settings);

        static void shutDown();

        static Mesh *makeMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                              unsigned int nElements, const unsigned int *elements);

        static Shader *makeShader(const std::string &shaderSource, Shader::ShaderType shaderType);

        static ShaderProgram *makeShaderProgram(unsigned int nShaders, const Shader *shaders);

        static Texture *makeTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);

        static PerspectiveCamera *makePerspectiveCamera();

        static OrthographicCamera *makeOrthographicCamera();
    };
}}
#endif
