#include <CSE/CSELL/render/gl/glrenderercomponentfactory.hpp>

#include <CSE/CSELL/render/gl/glshader.hpp>
#include <CSE/CSELL/render/gl/glshaderprogram.hpp>
#include <CSE/CSELL/render/gl/gltexture.hpp>
#include <CSE/CSELL/render/gl/glmesh.hpp>

namespace CSELL { namespace Render {
    Shader *GLRendererComponentFactory::makeNewShader() {
        return new GLShader();
    }

    ShaderProgram *GLRendererComponentFactory::makeNewShaderProgram() {
        return new GLShaderProgram();
    }

    Texture *GLRendererComponentFactory::makeNewTexture() {
        return new GLTexture();
    }

    Mesh *GLRendererComponentFactory::makeNewMesh() {
        return new GLMesh();
    }
}}
