#ifndef CSELL_RENDER_RENDERERCOMPONENTFACTORY_HPP
#define CSELL_RENDER_RENDERERCOMPONENTFACTORY_HPP

#include <CSE/CSELL/render/shader.hpp>
#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/mesh.hpp>

namespace CSELL { namespace Render {
    class Renderer;

    class RendererComponentFactory {
    friend class Renderer;
    protected:
        virtual Shader *makeNewShader();
        virtual ShaderProgram *makeNewShaderProgram();
        virtual Texture *makeNewTexture();
        virtual Mesh *makeNewMesh();
    };
}}

#endif
