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
        bool clearColour(float r, float g, float b, float a);
        bool clearDepth(float d);
        bool clearStencil(int i);
        bool clearAccum(float r, float g, float b, float a);
        bool setPolygonMode(bool enable);
    };
}}


#endif
