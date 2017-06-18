#ifndef CSELL_RENDER_RENDERER_HPP
#define CSELL_RENDER_RENDERER_HPP

#include <string>
#include <set>
#include <map>

#include <CSE/CSELL/core/window.hpp>

#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shaders.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/camera.hpp>

/*
    NOTE: This class assumes that an OPENGL context has been set up before use.
    Normally, if one were sticking with the prescribed interface, this should already be the case.
*/

namespace CSELL { namespace Render {
    class Renderer {
        static std::map<CSELL::Core::Window *, Renderer *> windows;
        static CSELL::Core::Window *activeWindowContext;

        std::string name;

        std::set<Shader *> shaders;
        std::set<ShaderProgram *> shaderPrograms;
        std::set<Texture *> textures;
        std::set<Mesh *> meshes;
        std::set<Camera *> cameras;

        CSELL::Core::Window *window;

        Renderer(const std::string &name, CSELL::Core::Window *window);

        void ensureActiveContext();
    public:
        static Renderer *newRenderer(const std::string &name, CSELL::Core::Window *window);

        std::string getName();

        ~Renderer();

        Shader *newShader(const std::string &shaderName, const std::string &shaderSource, Shader::ShaderType shaderType);

        ShaderProgram *newShaderProgram(const std::string &programName, unsigned int nShaders, const Shader **shaders);

        Texture *newTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);

        Mesh *newMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                      unsigned int nElements, const unsigned int *elements);

        OrthographicCamera *newOrthographicCamera(int screenWidth, int screenHeight, float unitsW, float unitsH);

        PerspectiveCamera *newPerspectiveCamera(int screenWidth, int screenHeight,
                                                 float fov, float aspectRatio, float near, float far);

        void deleteShader(Shader *shader);
        void deleteShaderProgram(ShaderProgram *shaderProgram);
        void deleteTexture(Texture *texture);
        void deleteCamera(Camera *camera);

        void renderState();
    };
}}
#endif
