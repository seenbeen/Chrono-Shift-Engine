#include <map>
#include <string>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>
#include <CSE/CSELL/render/texture.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Render {
    CacheManager::CacheManager() {}

    CacheManager::~CacheManager() {
        if (this->meshes.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Not all meshes are uncached at time of CacheManager deletion.");
        }
        if (this->shaderPrograms.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Not all shaderPrograms are uncached at time of CacheManager deletion.");
        }
        if (this->textures.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Not all textures are uncached at time of CacheManager deletion.");
        }
    }

    CSELL::Render::Mesh *CacheManager::retrieveMesh(std::string identifier) {
        std::map<std::string,CSELL::Render::Mesh*>::iterator it;
        it = this->meshes.find(identifier);
        if (it != this->meshes.end()) {
            return it->second;
        }
        return NULL;
    }

    CSELL::Render::ShaderProgram *CacheManager::retrieveShaderProgram(std::string identifier) {
        std::map<std::string,CSELL::Render::ShaderProgram*>::iterator it;
        it = this->shaderPrograms.find(identifier);
        if (it != this->shaderPrograms.end()) {
            return it->second;
        }
        return NULL;
    }

    CSELL::Render::Texture *CacheManager::retrieveTexture(std::string identifier) {
        std::map<std::string,CSELL::Render::Texture*>::iterator it;
        it = this->textures.find(identifier);
        if (it != this->textures.end()) {
            return it->second;
        }
        return NULL;
    }

    void CacheManager::cacheMesh(std::string identifier, CSELL::Render::Mesh *mesh) {
        this->meshes[identifier] = mesh;
    }

    void CacheManager::cacheShaderProgram(std::string identifier, CSELL::Render::ShaderProgram *shaderProgram) {
        this->shaderPrograms[identifier] = shaderProgram;
    }

    void CacheManager::cacheTexture(std::string identifier, CSELL::Render::Texture *texture) {
        this->textures[identifier] = texture;
    }

    void CacheManager::uncacheMesh(std::string identifier) {
        std::map<std::string,CSELL::Render::Mesh*>::iterator it;
        it = this->meshes.find(identifier);
        if (it != this->meshes.end()) {
            this->meshes.erase(it);
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                        "Trying to uncache non-cached Mesh.");
    }

    void CacheManager::uncacheShaderProgram(std::string identifier) {
        std::map<std::string,CSELL::Render::ShaderProgram*>::iterator it;
        it = this->shaderPrograms.find(identifier);
        if (it != this->shaderPrograms.end()) {
            this->shaderPrograms.erase(it);
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                        "Trying to uncache non-cached ShaderProgram.");
    }

    void CacheManager::uncacheTexture(std::string identifier) {
        std::map<std::string,CSELL::Render::Texture*>::iterator it;
        it = this->textures.find(identifier);
        if (it != this->textures.end()) {
            this->textures.erase(it);
        }
        CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                        "Trying to uncache non-cached Texture.");
    }
}}
