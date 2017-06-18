#include <cstddef>
#include <string>
#include <set>
#include <map>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>

#include <CSE/CSELL/core/window.hpp>

#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shaders.hpp>
#include <CSE/CSELL/render/texture.hpp>
#include <CSE/CSELL/render/camera.hpp>


namespace CSELL { namespace Render {
    std::map<CSELL::Core::Window *, Renderer *> Renderer::windows;
    CSELL::Core::Window *Renderer::activeWindowContext = NULL;

    Renderer::Renderer(const std::string &name, CSELL::Core::Window *window) {
        this->name = name;
        this->window = window;
    }

    void Renderer::ensureActiveContext() {
        if (Renderer::activeWindowContext != this->window) {
            this->window->useContext();
            Renderer::activeWindowContext = this->window;
        }
    }
    Renderer *Renderer::newRenderer(const std::string &name, CSELL::Core::Window *window) {
        if (Renderer::windows.find(window) != Renderer::windows.end()) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Failed to create Renderer! Renderer \"" +
                             Renderer::windows.find(window)->second->getName() + "\" already occupies window context!");
            return NULL;
        }
        Renderer *renderer = new Renderer(name, window);
        Renderer::windows[window] = renderer;
        return renderer;
    }

    std::string Renderer::getName() {
        return this->name;
    }

    Renderer::~Renderer() {
        this->ensureActiveContext();

        std::set<Shader *>::iterator shaderIt;
        for (shaderIt = shaders.begin(); shaderIt != shaders.end(); shaderIt++) {
            delete (*shaderIt);
        }

        std::set<ShaderProgram *>::iterator shaderProgramIt;
        for (shaderProgramIt = shaderPrograms.begin(); shaderProgramIt != shaderPrograms.end(); shaderProgramIt++) {
            delete (*shaderProgramIt);
        }

        std::set<Texture *>::iterator textureIt;
        for (textureIt = textures.begin(); textureIt != textures.end(); textureIt++) {
            delete (*textureIt);
        }

        /*
        std::set<Mesh *>::iterator meshIt;
        for (meshIt = meshes.begin(); meshIt != meshes.end(); meshIt++) {
            delete (*meshIt);
        }

        std::set<Camera *>::iterator camIt;
        for (camIt = cameras.begin(); camIt != cameras.end(); camIt++) {
            delete (*camIt);
        }
        */
        Renderer::windows.erase(Renderer::windows.find(this->window));
    }

    Shader *Renderer::newShader(const std::string &shaderName, const std::string &shaderSource, Shader::ShaderType shaderType) {
        this->ensureActiveContext();

        Shader *shader = new Shader(shaderName, shaderSource, shaderType);
        if (!shader->successfulCompile) {
            delete shader;
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Renderer",
                             "Failed to compile Shader for Renderer \"" + this->name + "\"!");
            return NULL;
        }
        this->shaders.insert(shader);
        return shader;
    }

    ShaderProgram *Renderer::newShaderProgram(const std::string &programName, unsigned int nShaders, const Shader **shaders) {
        this->ensureActiveContext();

        ShaderProgram *shaderProgram = new ShaderProgram(programName, nShaders, shaders);
        if (!shaderProgram->successfulLink) {
            delete shaderProgram;
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Renderer",
                             "Failed to compile ShaderProgram for Renderer \"" + this->name + "\"!");
            return NULL;
        }
        this->shaderPrograms.insert(shaderProgram);
        return shaderProgram;
    }

    Texture *Renderer::newTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData) {
        this->ensureActiveContext();
        Texture *texture = new Texture(imgW, imgH, imgData);
        this->textures.insert(texture);
        return texture;
    }

    OrthographicCamera *Renderer::newOrthographicCamera(int screenWidth, int screenHeight, float unitsW, float unitsH) {
        this->ensureActiveContext();

        return NULL;
    }

    PerspectiveCamera *Renderer::newPerspectiveCamera(int screenWidth, int screenHeight,
                                                       float fov, float aspectRatio, float near, float far) {
        this->ensureActiveContext();

        return NULL;
    }

    Mesh *Renderer::newMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                            unsigned int nElements, const unsigned int *elements) {
        this->ensureActiveContext();

        return NULL;
    }

    void Renderer::deleteShader(Shader *shader) {
        this->ensureActiveContext();

        std::set<Shader *>::iterator it = this->shaders.find(shader);
        if (it == this->shaders.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete Shader \"" + shader->getName() +
                             "\", which doesn't belong to renderer \"" + this->name + "\"!");
        } else {
            delete (*it);
            this->shaders.erase(it);
        }
    }

    void Renderer::deleteShaderProgram(ShaderProgram *shaderProgram) {
        this->ensureActiveContext();

        std::set<ShaderProgram *>::iterator it = this->shaderPrograms.find(shaderProgram);
        if (it == this->shaderPrograms.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete ShaderProgram \"" + shaderProgram->getName() +
                             "\", which doesn't belong to renderer \"" + this->name + "\"!");
        } else {
            delete (*it);
            this->shaderPrograms.erase(it);
        }
    }

    void Renderer::deleteTexture(Texture *texture) {
        this->ensureActiveContext();
        std::set<Texture *>::iterator it = this->textures.find(texture);
        if (it == this->textures.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete Texture which doesn't belong to renderer \"" +
                             this->name + "\"!");
        } else {
            delete (*it);
            this->textures.erase(it);
        }
    }

    void Renderer::deleteCamera(Camera *camera) {
        this->ensureActiveContext();

    }

    void Renderer::renderState() {
        this->ensureActiveContext();

    }
}}
