#include <CSE/CSEA/font/rasterizedfont.hpp>

#include <map>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/font/fontglyph.hpp>

namespace CSEA { namespace Font {
    RasterizedFont::RasterizedFont(std::map<char, unsigned int> glyphMap, unsigned int nGlyphs,
                                   unsigned int *glyphPackingOrder, CSELL::Font::FontGlyph **glyphs,
                                   unsigned int textureWidth, unsigned int textureHeight) {
        this->textureWidth = textureWidth;
        this->textureHeight = textureHeight;
        this->textureImage = new unsigned char[this->textureWidth * this->textureHeight * 4]; // rgba

        // time to pack c:
        unsigned int xMark = 0;
        unsigned int yMark = 0;
        unsigned int yTemp = 0;

        CSELL::Font::FontGlyph *currentGlyph;

        for (unsigned int i = 0; i < nGlyphs; ++i) {
            currentGlyph = glyphs[glyphPackingOrder[i]];
            if (xMark + currentGlyph->width > this->textureWidth) {
                xMark = 0;
                yMark += yTemp;
                yTemp = 0;
            }

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

        //delete[] this->offsetXs;
        //delete[] this->offsetYs;

        //delete[] this->texCoordXs;
        //delete[] this->texCoordYs;
        //delete[] this->meshCoordXs;
        //delete[] this->meshCoordYs;
    }

    unsigned int RasterizedFont::getTextureWidth() {
        return this->textureWidth;
    }

    unsigned int RasterizedFont::getTextureHeight() {
        return this->textureHeight;
    }

    unsigned char *RasterizedFont::getTextureImage() {
        return this->textureImage;
    }

    unsigned int *RasterizedFont::RasterizedFont::getTexCoordXs() {
        return this->texCoordXs;
    }

    unsigned int *RasterizedFont::getTexCoordYs() {
        return this->texCoordYs;
    }

    unsigned int *RasterizedFont::getMeshCoordXs() {
        return this->meshCoordXs;
    }

    unsigned int *RasterizedFont::getMeshCoordYs() {
        return this->meshCoordYs;
    }

    // returns false if glyph isn't available.
    bool RasterizedFont::queryGlyphData(char chr,
                        unsigned int &offsetX,
                        unsigned int &offsetY,
                        unsigned int &elementRangeBegin,
                        unsigned int &elementRangeEnd) {
        return true;
    }
}}
