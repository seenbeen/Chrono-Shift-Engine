#include <glad/glad.h>

#include <CSE/CSELL/render/gl/gltexture.hpp>

namespace CSELL { namespace Render {
    GLTexture::~GLTexture() {
        glDeleteTextures(1, &this->textureId);
    }

    bool GLTexture::initTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData) {
        glGenTextures(1,&this->textureId);
        glBindTexture(GL_TEXTURE_2D, this->textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgW, imgH, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
        //temp
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        return true;
    }

    bool GLTexture::useActiveTextureImplementation(unsigned int textureNumber) {
        glActiveTexture(GL_TEXTURE0 + textureNumber);
        glBindTexture(GL_TEXTURE_2D, this->textureId);

        return true;
    }
}}

