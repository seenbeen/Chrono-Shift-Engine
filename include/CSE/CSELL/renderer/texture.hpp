#ifndef CSELL_RENDERER_TEXTURE_HPP
#define CSELL_RENDERER_TEXTURE_HPP
#include <glad/glad.h>
#include <CSE/CSELL/asset/image.hpp>

namespace CSELL { namespace Renderer {
    class Texture {
    protected:
        unsigned int textureId;
    public:
        Texture(CSELL::Assets::ImageAsset *image);
        ~Texture();
        void useActiveTexture(GLenum textureNumber);
    };

    class Texture2D : public Texture {
    public:
        Texture2D(CSELL::Assets::ImageAsset *image);
    };
}}

#endif
