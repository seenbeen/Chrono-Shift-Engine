#include <map>
#include <string>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/renderer.hpp>
#include <CSE/CSELL/render/mesh.hpp>
#include <CSE/CSELL/render/shaderProgram.hpp>
#include <CSE/CSELL/render/texture.hpp>

#include <CSE/CSEA/render/cachemanager.hpp>

namespace CSEA { namespace Render {
    CacheManager::CacheManager(CSELL::Render::Renderer *renderer) {
        this->renderer = renderer;
    }

    CacheManager::~CacheManager() {
        std::map<std::string,unsigned int>::iterator refIt;
        for (refIt = this->meshReferences.begin(); refIt != this->meshReferences.end(); ++refIt){
            if (refIt->second) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                                "Not all Meshes are uncached at time of CacheManager deletion.");
                break;
            }
        }
        for (refIt = this->shaderProgramReferences.begin(); refIt != this->shaderProgramReferences.end(); ++refIt){
            if (refIt->second) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                                "Not all ShaderPrograms are uncached at time of CacheManager deletion.");
                break;
            }
        }
        for (refIt = this->textureReferences.begin(); refIt != this->textureReferences.end(); ++refIt){
            if (refIt->second) {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                                "Not all Textures are uncached at time of CacheManager deletion.");
                break;
            }
        }
        std::map<std::string,CSELL::Render::Mesh*>::iterator meshIt;
        for (meshIt = this->meshes.begin(); meshIt != this->meshes.end(); ++meshIt) {
            this->renderer->deleteMesh(meshIt->second);
        }
        std::map<std::string,CSELL::Render::ShaderProgram*>::iterator shaderProgramIt;
        for (shaderProgramIt = this->shaderPrograms.begin(); shaderProgramIt != this->shaderPrograms.end(); ++shaderProgramIt) {
            this->renderer->deleteShaderProgram(shaderProgramIt->second);
        }
        std::map<std::string,CSELL::Render::Texture*>::iterator textureIt;
        for (textureIt = this->textures.begin(); textureIt != this->textures.end(); ++textureIt) {
            this->renderer->deleteTexture(textureIt->second);
        }
    }

    CSELL::Render::Mesh *CacheManager::retrieveMesh(std::string identifier) {
        std::map<std::string,CSELL::Render::Mesh*>::iterator it;
        it = this->meshes.find(identifier);
        if (it != this->meshes.end()) {
            this->meshReferences[identifier]++;
            return it->second;
        }
        return NULL;
    }

    CSELL::Render::ShaderProgram *CacheManager::retrieveShaderProgram(std::string identifier) {
        std::map<std::string,CSELL::Render::ShaderProgram*>::iterator it;
        it = this->shaderPrograms.find(identifier);
        if (it != this->shaderPrograms.end()) {
            this->shaderProgramReferences[identifier]++;
            return it->second;
        }
        return NULL;
    }

    CSELL::Render::Texture *CacheManager::retrieveTexture(std::string identifier) {
        std::map<std::string,CSELL::Render::Texture*>::iterator it;
        it = this->textures.find(identifier);
        if (it != this->textures.end()) {
            this->textureReferences[identifier]++;
            return it->second;
        }
        return NULL;
    }

    void CacheManager::cacheMesh(std::string identifier, CSELL::Render::Mesh *mesh) {
        std::map<std::string,CSELL::Render::Mesh*>::iterator it;
        it = this->meshes.find(identifier);
        if (it != this->meshes.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Trying to cache already cached Mesh \""+identifier+"\".");
            return;
        }
        this->meshes[identifier] = mesh;
        this->meshReferences[identifier] = 1;
    }

    void CacheManager::cacheShaderProgram(std::string identifier, CSELL::Render::ShaderProgram *shaderProgram) {
        std::map<std::string,CSELL::Render::ShaderProgram*>::iterator it;
        it = this->shaderPrograms.find(identifier);
        if (it != this->shaderPrograms.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Trying to cache already cached ShaderProgram \""+identifier+"\".");
            return;
        }
        this->shaderPrograms[identifier] = shaderProgram;
        this->shaderProgramReferences[identifier] = 1;
    }

    void CacheManager::cacheTexture(std::string identifier, CSELL::Render::Texture *texture) {
        std::map<std::string,CSELL::Render::Texture*>::iterator it;
        it = this->textures.find(identifier);
        if (it != this->textures.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Trying to cache already cached Texture \""+identifier+"\".");
            return;
        }
        this->textures[identifier] = texture;
        this->textureReferences[identifier] = 1;
    }

    void CacheManager::releaseMesh(std::string identifier) {
        std::map<std::string,unsigned int>::iterator it = this->meshReferences.find(identifier);
        if (it == this->meshReferences.end() || !it->second) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Trying to release non-cached Mesh \""+identifier+"\".");
            return;
        }
        this->meshReferences[identifier]--;
    }

    void CacheManager::releaseShaderProgram(std::string identifier) {
        std::map<std::string,unsigned int>::iterator it = this->shaderProgramReferences.find(identifier);
        if (it == this->shaderProgramReferences.end() || !it->second) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Trying to release non-cached ShaderProgram \""+identifier+"\".");
            return;
        }
        this->shaderProgramReferences[identifier]--;
    }

    void CacheManager::releaseTexture(std::string identifier) {
        std::map<std::string,unsigned int>::iterator it = this->textureReferences.find(identifier);
        if (it == this->textureReferences.end() || !it->second) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Render - CacheManager",
                             "Trying to release non-cached Texture \""+identifier+"\".");
            return;
        }
        this->textureReferences[identifier]--;
    }
}}
