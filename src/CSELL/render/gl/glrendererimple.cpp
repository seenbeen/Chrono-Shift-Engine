#include <glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/gl/glrendererimple.hpp>

#include <CSE/CSELL/render/gl/glshader.hpp>
#include <CSE/CSELL/render/gl/glshaderprogram.hpp>
#include <CSE/CSELL/render/gl/gltexture.hpp>
#include <CSE/CSELL/render/gl/glmesh.hpp>

namespace CSELL { namespace Render {
    bool GLRendererImple::init() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        return true;
    }

    Shader *GLRendererImple::makeNewShader() {
        return new GLShader();
    }

    ShaderProgram *GLRendererImple::makeNewShaderProgram() {
        return new GLShaderProgram();
    }

    Texture *GLRendererImple::makeNewTexture() {
        return new GLTexture();
    }

    Mesh *GLRendererImple::makeNewMesh() {
        return new GLMesh();
    }

    bool GLRendererImple::setViewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        glViewport(x, y, w, h);
        return true;
    }

    bool GLRendererImple::clearColour(float r, float g, float b, float a) {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT);
        return true;
    }

    bool GLRendererImple::clearDepth(float d) {
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                         "Render - GLRendererImple",
                         "Method clearDepth unsupported atm!");
        return false;
    }

    bool GLRendererImple::clearStencil(int i) {
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                         "Render - GLRendererImple",
                         "Method clearStencil unsupported atm!");
        return false;
    }

    bool GLRendererImple::clearAccum(float r, float g, float b, float a) {
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                         "Render - GLRendererImple",
                         "Method clearAccum unsupported atm!");
        return false;
    }

    bool GLRendererImple::setPolygonMode(bool enable) {
        if (enable) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        return true;
    }
}}
