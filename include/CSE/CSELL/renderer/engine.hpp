#ifndef CSELL_RENDERER_ENGINE_HPP
#define CSELL_RENDERER_ENGINE_HPP

#include <string>

#include <lib/glad/glad.h>
#include <lib/glfw/glfw3.h>

#include <CSE/CSELL/renderer/mesh.hpp>
#include <CSE/CSELL/renderer/shaders.hpp>
#include <CSE/CSELL/renderer/texture.hpp>
#include <CSE/CSELL/renderer/camera.hpp>

namespace CSELL { namespace Renderer {
    struct RenderEngineSettings {
        unsigned int windowWidth, windowHeight;
        bool resizeable;
        std::string windowName;
        void *inputCallBack;
    };

    class RenderEngine {
        static bool isInitialized;
        static GLFWwindow *window;
        static unsigned int windowWidth, windowHeight;

        static bool ensureIsInitialized();
    public:
        static bool initialize(const RenderEngineSettings &settings);

        static void shutdown();

        static void resize(unsigned int width, unsigned int height);

        static GLFWwindow *getWindow();

        static void renderState();

        static Mesh *makeMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                              unsigned int nElements, const unsigned int *elements);

        static Shader *makeShader(const std::string &shaderSource, Shader::ShaderType shaderType);

        static ShaderProgram *makeShaderProgram(unsigned int nShaders, const Shader *shaders);

        static Texture *makeTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);

        static OrthographicCamera *makeOrthographicCamera(int screenWidth, int screenHeight, float unitsW, float unitsH);

        static PerspectiveCamera *makePerspectiveCamera(int screenWidth, int screenHeight,
                                                        float fov, float aspectRatio, float near, float far);
    };
}}
#endif
