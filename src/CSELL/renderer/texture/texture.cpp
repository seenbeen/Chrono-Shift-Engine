#include <glad/glad.h>
#include <CSELL/asset/image/image.h>
#include <CSELL/renderer/texture/texture.h>

namespace CSELL { namespace Renderer {
    Texture::Texture(CSELL::Asset::ImageAsset *image) {
        glGenTextures(1,&this->textureId);
        glBindTexture(GL_TEXTURE_2D, this->textureId);

        GLenum format = GL_RGB;

        if (image->nChannels() == 4) {
            format = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, image->width(), image->height(),
                    0, format, GL_UNSIGNED_BYTE, image->data());
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::useActiveTexture(GLenum textureNumber) {
        glActiveTexture(textureNumber);
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &this->textureId);
    }

    Texture2D::Texture2D(CSELL::Asset::ImageAsset *image) : Texture(image) {
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}}
