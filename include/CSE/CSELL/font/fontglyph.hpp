#ifndef CSELL_FONT_FONTGLYPH_HPP
#define CSELL_FONT_FONTGLYPH_HPP

namespace CSELL { namespace Font {
    struct FontGlyph {
        unsigned int bearingX;
        unsigned int bearingY;
        unsigned int width;
        unsigned int height;
        unsigned int advance;
        unsigned char *buffer; // each pixel is one byte

        FontGlyph(unsigned int bearingX, unsigned int bearingY,
                  unsigned int width, unsigned int height,
                  unsigned int advance, unsigned char *buffer);
        ~FontGlyph();
    };
}}
#endif // CSELL_FONT_FONTGLYPH_HPP
