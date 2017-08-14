#include <CSE/CSEA/font/rasterizedfont.hpp>

#include <map>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/font/fontglyph.hpp>

namespace CSEA { namespace Font {
    RasterizedFont::RasterizedFont(unsigned int nGlyphs,
                                   unsigned int *glyphPackingOrder, CSELL::Font::FontGlyph **glyphs,
                                   unsigned int textureWidth, unsigned int textureHeight) {
        this->nGlyphs = nGlyphs;
        this->textureWidth = textureWidth;
        this->textureHeight = textureHeight;
        this->textureImage = new unsigned char[this->textureWidth * this->textureHeight * 4]; // rgba

        this->offsetXs = new int[this->nGlyphs];
        this->offsetYs = new int[this->nGlyphs];
        this->advanceXs = new int[this->nGlyphs];

        this->glyphXs = new int[this->nGlyphs];
        this->glyphYs = new int[this->nGlyphs];
        this->glyphWidths = new int[this->nGlyphs];
        this->glyphHeights = new int[this->nGlyphs];


        // time to pack c:
        unsigned int xMark = 0;
        unsigned int yMark = 0;
        unsigned int yTemp = 0;

        CSELL::Font::FontGlyph *currentGlyph;

        for (unsigned int i = 0; i < this->nGlyphs; ++i) {
            currentGlyph = glyphs[glyphPackingOrder[i]];
            this->glyphMap[currentGlyph->chr] = i;

            if (xMark + currentGlyph->width > this->textureWidth) {
                xMark = 0;
                yMark += yTemp;
                yTemp = 0;
            }

            this->offsetXs[i] = currentGlyph->bearingX;
            this->offsetYs[i] = currentGlyph->bearingY;
            this->advanceXs[i] = currentGlyph->advance;

            this->glyphXs[i] = xMark;
            this->glyphYs[i] = yMark;
            this->glyphWidths[i] = currentGlyph->width;
            this->glyphHeights[i] = currentGlyph->height;

            // fill in our glyph
            for (unsigned int glyphY = 0; glyphY < currentGlyph->height; ++glyphY) {
                for (unsigned int glyphX = 0; glyphX < currentGlyph->width; ++glyphX) {
                    unsigned int texIndex = ((yMark + glyphY) * this->textureWidth + xMark + glyphX) * 4;
                    unsigned int glyphIndex = glyphY * currentGlyph->width + glyphX;

                    for (unsigned int col = 0; col < 3; col++) {
                        this->textureImage[texIndex + col] = 255;
                    }

                    this->textureImage[texIndex + 3] = currentGlyph->buffer[glyphIndex];
                }
            }

            xMark += currentGlyph->width;
            yTemp = std::max(yTemp, currentGlyph->height);
        }
    }

    RasterizedFont::~RasterizedFont() {
        delete[] this->textureImage;

        delete[] this->offsetXs;
        delete[] this->offsetYs;
        delete[] this->advanceXs;

        delete[] this->glyphXs;
        delete[] this->glyphYs;
        delete[] this->glyphWidths;
        delete[] this->glyphHeights;
    }

    unsigned int RasterizedFont::getNGlyphs() {
        return this->nGlyphs;
    }

    int RasterizedFont::getTextureWidth() {
        return this->textureWidth;
    }

    int RasterizedFont::getTextureHeight() {
        return this->textureHeight;
    }

    unsigned char *RasterizedFont::getTextureImage() {
        return this->textureImage;
    }

    int *RasterizedFont::getGlyphXs() {
        return this->glyphXs;
    }

    int *RasterizedFont::getGlyphYs() {
        return this->glyphYs;
    }

    int *RasterizedFont::getGlyphWidths() {
        return this->glyphWidths;
    }

    int *RasterizedFont::getGlyphHeights() {
        return this->glyphHeights;
    }

    // returns false if glyph isn't available.
    bool RasterizedFont::queryGlyphData(char chr,
                                        int &offsetX,
                                        int &offsetY,
                                        int &advanceX,
                                        int &glyphIndex) {

        std::map<char,unsigned int>::iterator it = this->glyphMap.find(chr);

        if (it == this->glyphMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - RasterizedFont",
                             "Character " + std::string(&chr) + " was not available.");
            return false;
        }

        glyphIndex = it->second;
        offsetX = this->offsetXs[glyphIndex];
        offsetY = this->offsetYs[glyphIndex];
        advanceX = this->advanceXs[glyphIndex];

        return true;
    }
}}
