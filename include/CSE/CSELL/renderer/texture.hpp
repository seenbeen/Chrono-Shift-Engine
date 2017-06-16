#ifndef CSELL_RENDERER_TEXTURE_HPP
#define CSELL_RENDERER_TEXTURE_HPP

#include <glad/glad.h>

namespace CSELL { namespace Renderer {
    class Texture {
    protected:
        unsigned int textureId;
    public:
        Texture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);
        ~Texture();
        void bindTexture();
        void useActiveTexture(GLenum textureNumber);
    };

    class Texture2D : public Texture {
        void initTexture();
    };
}}

#endif
