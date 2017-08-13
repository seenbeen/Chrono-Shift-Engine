#include <CSE/CSELL/font/fontglyph.hpp>

#include <algorithm>

namespace CSELL { namespace Font {
    FontGlyph::FontGlyph(unsigned int bearingX, unsigned int bearingY,
                         unsigned int width, unsigned int height,
                         unsigned int advance, unsigned char *buffer) {
        this->bearingX = bearingX;
        this->bearingY = bearingY;
        this->width = width;
        this->height = height;
        this->advance = advance;
        this->buffer = new unsigned char[this->width * this->height]; // note each pixel is only a single char
        std::copy(this->buffer, this->buffer + this->width * this->height, buffer);
    }

    FontGlyph::~FontGlyph() {
        delete[] this->buffer;
    }
}}
