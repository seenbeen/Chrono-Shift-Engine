#ifndef CSEA_FONT_RASTERIZEDFONT_HPP
#define CSEA_FONT_RASTERIZEDFONT_HPP

namespace CSEA { namespace Font {
    /*
        Rasterized Font class, which essentially packs all characters requested
        by the call to FontRasterizer into a texture. Handles all necessary
        coordinate work in order to properly render a font into the screen,
        and will warn if a character that was requested was not loaded.
    */

    class FontRasterizer;

    class RasterizedFont {
    friend class FontRasterized;

    public:
        unsigned int getTextureWidth();
        unsigned int getTextureHeight();
        unsigned char *getTextureData();

        // returns false if glyph isn't available.
        bool queryGlyphData(char chr,
                            unsigned int &offsetX,
                            unsigned int &offsetY,
                            unsigned int &elementRangeBegin,
                            unsigned int &elementRangeEnd);
    };
}}
#endif // CSEA_FONT_RASTERIZEDFONT_HPP
