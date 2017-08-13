#ifndef CSELL_FONT_FONTENGINE_HPP
#define CSELL_FONT_FONTENGINE_HPP

#include <utility>
#include <string>
#include <map>

// freetypee
#include <ft2build.h>
#include FT_FREETYPE_H

#include <CSE/CSELL/font/fontglyph.hpp>

namespace CSELL { namespace Font {
    /*
        Static Class for abstracting away certain font functions from CSEA engine layer.
        Implemented using FreeType.
    */
    class FontEngine {
        FontEngine();
        ~FontEngine();

        static bool isInitialized;
        static FT_Library ft;
        static std::map<std::string,FT_Face> fontFaceMap;
        static std::map<std::string,std::map<std::pair<char,unsigned int>,FontGlyph*>> fontGlyphMap;

    public:
        static bool initialize();
        static void shutdown();
        static bool loadFont(const std::string &fontPath, const std::string &fontKey);
        static bool unloadFont(const std::string &fontKey);
        static FontGlyph *getGlyph(const std::string &fontKey, const char chr, unsigned int fontSize);
    };
}}

#endif // CSELL_FONT_FONTENGINE_HPP
