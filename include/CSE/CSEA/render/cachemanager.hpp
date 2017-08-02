#ifndef CSEA_RENDER_CACHEMANAGER_HPP
#define CSEA_RENDER_CACHEMANAGER_HPP
#include <map>
#include <string>

#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>
#include <CSE/CSELL/render/texture.hpp>

namespace CSEA { namespace Render {
    class CacheManager {
        std::map<std::string,CSELL::Render::Mesh*> meshes;
        std::map<std::string,CSELL::Render::ShaderProgram*> shaderPrograms;
        std::map<std::string,CSELL::Render::Texture*> textures;
    public:
        CacheManager();
        ~CacheManager();

        CSELL::Render::Mesh *retrieveMesh(std::string identifier);
        CSELL::Render::ShaderProgram *retrieveShaderProgram(std::string identifier);
        CSELL::Render::Texture *retrieveTexture(std::string identifier);

        void cacheMesh(std::string identifier, CSELL::Render::Mesh *mesh);
        void cacheShaderProgram(std::string identifier, CSELL::Render::ShaderProgram *shaderProgram);
        void cacheTexture(std::string identifier, CSELL::Render::Texture *texture);

        void uncacheMesh(std::string identifier);
        void uncacheShaderProgram(std::string identifier);
        void uncacheTexture(std::string identifier);
    };
}}

#endif
