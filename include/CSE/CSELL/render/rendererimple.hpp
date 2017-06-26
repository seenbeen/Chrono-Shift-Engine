#ifndef CSELL_RENDER_RENDERERIMPLE_HPP
#define CSELL_RENDER_RENDERERIMPLE_HPP

#include <CSE/CSELL/render/shader.hpp>
#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/mesh.hpp>

namespace CSELL { namespace Render {
    class Renderer;

    class RendererImple {
    friend class Renderer;
    protected:
        virtual bool init() = 0;
        virtual Shader *makeNewShader() = 0;
        virtual ShaderProgram *makeNewShaderProgram() = 0;
        virtual Texture *makeNewTexture() = 0;
        virtual Mesh *makeNewMesh() = 0;
        virtual bool setViewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h) = 0;
    };
}}

#endif
