#include <glad/glad.h>

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
}}
