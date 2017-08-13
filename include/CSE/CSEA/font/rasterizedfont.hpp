#ifndef CSEA_FONT_RASTERIZEDFONT_HPP
#define CSEA_FONT_RASTERIZEDFONT_HPP

#include <map>

#include <CSE/CSELL/font/fontglyph.hpp>

namespace CSEA { namespace Font {
    /*
        Rasterized Font class, which essentially packs all characters requested
        by the call to FontRasterizer into a texture. Handles all necessary
        coordinate work in order to properly render a font into the screen,
        and will warn if a character that was requested was not loaded.
    */

    class FontRasterizer;

    class RasterizedFont {
    friend class FontRasterizer;
        unsigned int nGlyphs;
        unsigned int textureWidth, textureHeight;
        unsigned char *textureImage;

        std::map<char, unsigned int> glyphMap;
        unsigned int *offsetXs;
        unsigned int *offsetYs;
        unsigned int *advanceXs;

        unsigned int *glyphXs;
        unsigned int *glyphYs;
        unsigned int *glyphWidths;
        unsigned int *glyphHeights;

        RasterizedFont(unsigned int nGlyphs,
                       unsigned int *glyphPackingOrder, CSELL::Font::FontGlyph **glyphs,
                       unsigned int textureWidth, unsigned int textureHeight);
        ~RasterizedFont();
    public:
        unsigned int getTextureWidth();
        unsigned int getTextureHeight();
        unsigned char *getTextureImage();

        unsigned int getNGlyphs();
        unsigned int *getGlyphXs();
        unsigned int *getGlyphYs();
        unsigned int *getGlyphWidths();
        unsigned int *getGlyphHeights();

        // returns false if glyph isn't available.
        bool queryGlyphData(char chr, unsigned int &offsetX, unsigned int &offsetY,
                            unsigned int &advanceX, unsigned int &glyphIndex);
    };
}}
#endif // CSEA_FONT_RASTERIZEDFONT_HPP
