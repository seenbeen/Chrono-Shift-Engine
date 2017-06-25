#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/texture.hpp>

namespace CSELL { namespace Render {
    Texture::Texture() {}
    Texture::~Texture() {}
    bool Texture::useActiveTexture(unsigned int textureNumber) {
        #if RENDERER_WARNING_CHECKS == true
        if (this->renderer != *this->activeRenderer) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Texture",
                             "Texture does not belong to active Renderer!");
            return false;
        }
        #endif
        return this->useActiveTextureImplementation(textureNumber);
    }
}}
