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
        int textureWidth, textureHeight;
        unsigned char *textureImage;

        std::map<char, unsigned int> glyphMap;
        int *offsetXs;
        int *offsetYs;
        int *advanceXs;

        int *glyphXs;
        int *glyphYs;
        int *glyphWidths;
        int *glyphHeights;

        RasterizedFont(unsigned int nGlyphs,
                       unsigned int *glyphPackingOrder, CSELL::Font::FontGlyph **glyphs,
                       unsigned int textureWidth, unsigned int textureHeight);
        ~RasterizedFont();
    public:
        int getTextureWidth();
        int getTextureHeight();
        unsigned char *getTextureImage();

        unsigned int getNGlyphs();
        int *getGlyphXs();
        int *getGlyphYs();
        int *getGlyphWidths();
        int *getGlyphHeights();

        // returns false if glyph isn't available.
        bool queryGlyphData(char chr, int &offsetX, int &offsetY,
                            int &advanceX, int &glyphIndex);
    };
}}
#endif // CSEA_FONT_RASTERIZEDFONT_HPP
