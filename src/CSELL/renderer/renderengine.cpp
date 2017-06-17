#include <cstddef>
#include <string>

#include <lib/glad/glad.h>
#include <lib/glfw/glfw3.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/renderer/renderengine.hpp>
#include <CSE/CSELL/renderer/mesh.hpp>
#include <CSE/CSELL/renderer/shaders.hpp>
#include <CSE/CSELL/renderer/texture.hpp>
#include <CSE/CSELL/renderer/camera.hpp>

namespace CSELL { namespace Renderer {
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        RenderEngine::resize(width, height);
    }

    bool RenderEngine::isInitialized = false;
    GLFWwindow* RenderEngine::window = NULL;
    unsigned int RenderEngine::windowWidth = 0;
    unsigned int RenderEngine::windowHeight = 0;

    bool RenderEngine::ensureIsInitialized() {
        if (!RenderEngine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "RenderEngine", "RenderEngine not Initialized!");
            return false;
        }
        return true;
    }

    bool RenderEngine::initialize(const RenderEngineSettings &settings) {
        if (RenderEngine::isInitialized) {
            return false;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        RenderEngine::isInitialized = true;

        glfwSetFramebufferSizeCallback(RenderEngine::window, framebuffer_size_callback);

        return true;
    }

    void RenderEngine::shutdown() {
        // free up all resources allocated
        if (!RenderEngine::ensureIsInitialized()) {
            return;
        }
        glfwTerminate();
    }

    void RenderEngine::resize(unsigned int width, unsigned int height) {
        if (!RenderEngine::ensureIsInitialized()) {
            return;
        }
        RenderEngine::windowWidth = width;
        RenderEngine::windowHeight = height;
    }

    GLFWwindow *RenderEngine::getWindow() { return RenderEngine::window; }

    void RenderEngine::renderState() {}

    Mesh *RenderEngine::makeMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                                 unsigned int nElements, const unsigned int *elements) {
        return NULL;
    }

    Shader *RenderEngine::makeShader(const std::string &shaderSource, Shader::ShaderType shaderType) {
        return NULL;
    }

    ShaderProgram *RenderEngine::makeShaderProgram(unsigned int nShaders, const Shader *shaders) {
        return NULL;
    }

    Texture *RenderEngine::makeTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData) {
        return NULL;
    }

    OrthographicCamera *RenderEngine::makeOrthographicCamera(int screenWidth, int screenHeight, float unitsW, float unitsH) {
        return NULL;
    }

    PerspectiveCamera *RenderEngine::makePerspectiveCamera(int screenWidth, int screenHeight,
                                                           float fov, float aspectRatio, float near, float far) {
        return NULL;
    }
}}
