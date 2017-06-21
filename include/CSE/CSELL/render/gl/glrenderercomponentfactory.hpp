#ifndef CSELL_RENDER_GL_GLRENDERERCOMPONENTFACTORY_HPP
#define CSELL_RENDER_GL_GLRENDERERCOMPONENTFACTORY_HPP

#include <CSE/CSELL/render/renderercomponentfactory.hpp>

namespace CSELL { namespace Render {
    class Shader;
    class ShaderProgram;
    class Texture;
    class Mesh;

    class GLRendererComponentFactory: public RendererComponentFactory {
    protected:
        Shader *makeNewShader();
        ShaderProgram *makeNewShaderProgram();
        Texture *makeNewTexture();
        Mesh *makeNewMesh();
    };
}}


#endif
