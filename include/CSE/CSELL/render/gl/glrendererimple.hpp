#ifndef CSELL_RENDER_GL_GLRENDERERIMPLE_HPP
#define CSELL_RENDER_GL_GLRENDERERIMPLE_HPP

#include <CSE/CSELL/render/rendererimple.hpp>

namespace CSELL { namespace Render {
    class Shader;
    class ShaderProgram;
    class Texture;
    class Mesh;

    class GLRendererImple: public RendererImple {
    protected:
        bool init();
        Shader *makeNewShader();
        ShaderProgram *makeNewShaderProgram();
        Texture *makeNewTexture();
        Mesh *makeNewMesh();
        bool setViewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    };
}}


#endif
