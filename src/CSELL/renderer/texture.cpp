#include <glad/glad.h>

#include <CSE/CSELL/renderer/texture.hpp>

namespace CSELL { namespace Renderer {
    Texture::Texture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData) {
        glGenTextures(1,&this->textureId);
        glBindTexture(GL_TEXTURE_2D, this->textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgW, imgH, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
        //temp
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void Texture::bindTexture() {
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }

    void Texture::useActiveTexture(GLenum textureNumber) {
        glActiveTexture(textureNumber);
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &this->textureId);
    }
}}
