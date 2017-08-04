#include <set>
#include <map>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/core/window.hpp>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/rendererimple.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shader.hpp>
#include <CSE/CSELL/render/shaderprogram.hpp>
#include <CSE/CSELL/render/texture.hpp>


namespace CSELL { namespace Render {
    #if RENDERER_WARNING_CHECKS == true
    std::map<CSELL::Core::Window *, Renderer *> Renderer::windows;
    Renderer *Renderer::activeRenderer = NULL;
    #endif

    Renderer::Renderer(CSELL::Core::Window *window, RendererImple *rImple)
                    : window(window), rImple(rImple) {
        #if RENDERER_WARNING_CHECKS == true
        this->activeRenderer = NULL;
        #endif
    }

    Renderer *Renderer::newRenderer(CSELL::Core::Window *window, RendererImple *rImple) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::windows.find(window) != Renderer::windows.end()) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Failed to create Renderer! Window context already occupied!");
            return NULL;
        }

        if (!rImple->init()) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Failed to create Renderer! RendererImple failed to initialize!");
            return NULL;
        }

        Renderer *renderer = new Renderer(window, rImple);
        Renderer::windows[window] = renderer;

        #else
        rImple->init();
        Renderer *renderer = new Renderer(window, rImple);
        #endif

        return renderer;
    }

    Renderer::~Renderer() {
        #if RENDERER_WARNING_CHECKS == true
        Renderer *activeRendererBack = Renderer::activeRenderer;
        if (activeRendererBack != Renderer::activeRenderer) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Deleting renderer whose context isn't active!");
        }
        // ensure renderer context matches
        Renderer::activeRenderer = this;
        this->window->useContext();

        if (shaders.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Not all shaders freed on renderer deletion!");
        }
        if (shaderPrograms.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Not all shader programs freed on renderer deletion!");
        }
        if (textures.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Not all textures freed on renderer deletion!");
        }
        if (meshes.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Not all meshes freed on renderer deletion!");
        }

        #endif

        std::set<Shader *>::iterator shaderIt;
        for (shaderIt = shaders.begin(); shaderIt != shaders.end(); ++shaderIt) {
            delete (*shaderIt);
        }

        std::set<ShaderProgram *>::iterator shaderProgramIt;
        for (shaderProgramIt = shaderPrograms.begin(); shaderProgramIt != shaderPrograms.end(); ++shaderProgramIt) {
            delete (*shaderProgramIt);
        }

        std::set<Texture *>::iterator textureIt;
        for (textureIt = textures.begin(); textureIt != textures.end(); ++textureIt) {
            delete (*textureIt);
        }

        std::set<Mesh *>::iterator meshIt;
        for (meshIt = meshes.begin(); meshIt != meshes.end(); ++meshIt) {
            delete (*meshIt);
        }

        #if RENDERER_WARNING_CHECKS == true
        Renderer::windows.erase(Renderer::windows.find(this->window));

        // restore context if we didn't delete the currently active renderer
        if (this == activeRendererBack) {
            Renderer::activeRenderer = NULL;
        } else {
            activeRendererBack->makeActiveRenderer();
        }
        #endif
    }

    bool Renderer::makeActiveRenderer() {
        #if RENDERER_WARNING_CHECKS == true
        if (this == Renderer::activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                 "Render - Renderer",
                 "Window context already active!");
            return false;
        }

        Renderer::activeRenderer = this;
        #endif

        this->window->useContext();
        return true;
    }

    Shader *Renderer::newShader(const char *shaderSource, Shader::ShaderType shaderType) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return NULL;
        }
        #endif

        Shader *shader = this->rImple->makeNewShader();

        #if RENDERER_WARNING_CHECKS == true
        if (!shader->initShader(shaderSource, shaderType)) {
            delete shader;
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Renderer",
                             "Failed to initialize Shader!");
            return NULL;
        }
        shader->renderer = this;
        shader->activeRenderer = &Renderer::activeRenderer;
        #else
        shader->initShader(shaderSource, shaderType);
        #endif

        this->shaders.insert(shader);
        return shader;
    }

    ShaderProgram *Renderer::newShaderProgram() {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return NULL;
        }
        #endif

        ShaderProgram *shaderProgram = this->rImple->makeNewShaderProgram();

        #if RENDERER_WARNING_CHECKS == true
        if (!shaderProgram->initShaderProgram()) {
            delete shaderProgram;
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Renderer",
                             "Failed to initialize ShaderProgram!");
            return NULL;
        }

        shaderProgram->renderer = this;
        shaderProgram->activeRenderer = &Renderer::activeRenderer;
        #else
        shaderProgram->initShaderProgram();
        #endif

        this->shaderPrograms.insert(shaderProgram);
        return shaderProgram;
    }

    Texture *Renderer::newTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return NULL;
        }
        #endif

        Texture *texture = this->rImple->makeNewTexture();

        #if RENDERER_WARNING_CHECKS == true
        if (!texture->initTexture(imgW, imgH, imgData)) {
            delete texture;
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Renderer",
                             "Failed to initialize Texture!");
            return NULL;
        }
        texture->renderer = this;
        texture->activeRenderer = &Renderer::activeRenderer;
        #else
        texture->initTexture(imgW, imgH, imgData);
        #endif

        this->textures.insert(texture);
        return texture;
    }

    Mesh *Renderer::newMesh(unsigned int nVertices, const Mesh::Vertex *vertices,
                            unsigned int nElements, const unsigned int *elements) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return NULL;
        }
        #endif

        Mesh *mesh = this->rImple->makeNewMesh();

        #if RENDERER_WARNING_CHECKS == true
        if (!mesh->initMesh(nVertices, vertices, nElements, elements)) {
            delete mesh;
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Renderer",
                             "Failed to initialize Mesh!");
            return NULL;
        }
        mesh->renderer = this;
        mesh->activeRenderer = &Renderer::activeRenderer;
        #else
        mesh->initMesh(nVertices, vertices, nElements, elements);
        #endif

        this->meshes.insert(mesh);
        return mesh;
    }

    bool Renderer::deleteShader(Shader *shader) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        std::set<Shader *>::iterator it = this->shaders.find(shader);

        #if RENDERER_WARNING_CHECKS == true
        if (it == this->shaders.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete Shader not belonging to renderer!");
            return false;
        } else {
            delete shader;
            this->shaders.erase(it);
            return true;
        }
        #else
        delete shader;
        this->shaders.erase(it);
        return true;
        #endif
    }

    bool Renderer::deleteShaderProgram(ShaderProgram *shaderProgram) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        std::set<ShaderProgram *>::iterator it = this->shaderPrograms.find(shaderProgram);

        #if RENDERER_WARNING_CHECKS == true
        if (it == this->shaderPrograms.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete ShaderProgram not belonging to renderer!");
            return false;
        } else {
            delete shaderProgram;
            this->shaderPrograms.erase(it);
            return true;
        }
        #else
        delete shaderProgram;
        this->shaderPrograms.erase(it);
        return true;
        #endif
    }

    bool Renderer::deleteTexture(Texture *texture) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        std::set<Texture *>::iterator it = this->textures.find(texture);

        #if RENDERER_WARNING_CHECKS == true
        if (it == this->textures.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete Texture not belonging to renderer!");
            return false;
        } else {
            delete texture;
            this->textures.erase(it);
            return true;
        }
        #else
        delete texture;
        this->textures.erase(it);
        return true;
        #endif
    }

    bool Renderer::deleteMesh(Mesh *mesh) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        std::set<Mesh *>::iterator it = this->meshes.find(mesh);

        #if RENDERER_WARNING_CHECKS == true
        if (it == this->meshes.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                             "Render - Renderer",
                             "Trying to delete Mesh not belonging to renderer!");
            return false;
        } else {
            delete mesh;
            this->meshes.erase(it);
            return true;
        }
        #else
        delete mesh;
        this->meshes.erase(it);
        return true;
        #endif
    }

    bool Renderer::setViewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        return this->rImple->setViewport(x,y,w,h);
    }

    bool Renderer::clearColour(float r, float g, float b, float a) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        return this->rImple->clearColour(r,g,b,a);
    }

    bool Renderer::clearDepth(float d) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        if (d < 0.0f || d > 1.0f) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "clearDepth takes float in range [0,1]!");
            return false;
        }
        #endif

        return this->rImple->clearDepth(d);
    }

    bool Renderer::clearStencil(int i) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        return this->rImple->clearStencil(i);
    }

    bool Renderer::clearAccum(float r, float g, float b, float a) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        return this->rImple->clearAccum(r,g,b,a);
    }

    bool Renderer::setPolygonMode(bool enable) {
        #if RENDERER_WARNING_CHECKS == true
        if (Renderer::activeRenderer != this) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL,
                            "Render - Renderer",
                            "Renderer is not the active renderer!");
            return false;
        }
        #endif

        return this->rImple->setPolygonMode(enable);
    }
}}
