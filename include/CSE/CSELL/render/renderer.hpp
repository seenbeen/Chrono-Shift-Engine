#ifndef CSELL_RENDER_RENDERER_HPP
#define CSELL_RENDER_RENDERER_HPP

#include <set>
#include <map>

#include <CSE/CSELL/core/window.hpp>

#include <CSE/CSELL/render/renderercomponentfactory.hpp>
#include <CSE/CSELL/render/shader.hpp>
#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/mesh.hpp>
/*
    NOTE: This class assumes that an OPENGL context has been set up before use.
    Normally, if one were sticking with the prescribed interface, this should already be the case.
*/

namespace CSELL { namespace Render {
    class Renderer {
        #if RENDERER_WARNING_CHECKS == true
        static std::map<CSELL::Core::Window *, Renderer *> windows;
        static Renderer *activeRenderer;
        #endif

        std::set<Shader *> shaders;
        std::set<ShaderProgram *> shaderPrograms;
        std::set<Texture *> textures;
        std::set<Mesh *> meshes;

        CSELL::Core::Window *window;
        RendererComponentFactory *factory;

        Renderer(CSELL::Core::Window *window, RendererComponentFactory *factory);

    public:
        static Renderer *newRenderer(CSELL::Core::Window *window, RendererComponentFactory *factory);
        ~Renderer();

        bool makeActiveRenderer();

        Shader *newShader(const char *shaderSource, Shader::ShaderType shaderType);
        ShaderProgram *newShaderProgram();
        Texture *newTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);
        Mesh *newMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                      unsigned int nElements, const unsigned int *elements);

        bool deleteShader(Shader *shader);
        bool deleteShaderProgram(ShaderProgram *shaderProgram);
        bool deleteTexture(Texture *texture);
        bool deleteMesh(Mesh *mesh);
    };
}}
#endif
