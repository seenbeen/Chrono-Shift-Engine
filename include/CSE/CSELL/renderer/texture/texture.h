#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <CSE/CSELL/asset/image/image.h>

namespace CSELL { namespace Renderer {
    class Texture {
    protected:
        unsigned int textureId;
    public:
        Texture(CSELL::Asset::ImageAsset *image);
        ~Texture();
        void useActiveTexture(GLenum textureNumber);
    };

    class Texture2D : public Texture {
    public:
        Texture2D(CSELL::Asset::ImageAsset *image);
    };
}}

#endif
