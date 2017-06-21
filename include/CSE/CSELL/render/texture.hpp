#ifndef CSELL_RENDER_TEXTURE_HPP
#define CSELL_RENDER_TEXTURE_HPP

namespace CSELL { namespace Render {
    class Renderer;

    class Texture {
    friend class Renderer;
        Renderer *renderer;
        Renderer **activeRenderer;
    protected:
        Texture();
        virtual ~Texture();

        virtual bool initTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData) = 0;
        virtual bool useActiveTextureImplementation(unsigned int textureNumber) = 0;
    public:
        bool useActiveTexture(unsigned int textureNumber);
    };
}}

#endif
