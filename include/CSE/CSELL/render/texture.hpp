#ifndef CSELL_RENDER_TEXTURE_HPP
#define CSELL_RENDER_TEXTURE_HPP

#include <glad/glad.h>

namespace CSELL { namespace Render {
    class Renderer;

    class Texture {
    friend class Renderer;
        static unsigned int activeTexture;
        unsigned int textureId;
        Texture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);
        ~Texture();
    public:
        void useActiveTexture(unsigned int textureNumber);
    };

}}

#endif
