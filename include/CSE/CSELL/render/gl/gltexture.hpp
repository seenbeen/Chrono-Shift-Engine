#ifndef CSELL_RENDER_GL_GLTEXTURE_HPP
#define CSELL_RENDER_GL_GLTEXTURE_HPP

#include <CSE/CSELL/render/texture.hpp>

namespace CSELL { namespace Render {
    class GLTexture: public Texture {
        unsigned int textureId;
    protected:
        ~GLTexture();
        bool initTexture(unsigned int imgW, unsigned int imgH, const unsigned char *imgData);
        bool useActiveTextureImplementation(unsigned int textureNumber);
    };

}}

#endif
