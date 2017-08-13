#include <CSE/CSELL/font/fontengine.hpp>

#include <utility>
#include <string>
#include <map>

// freetypee
#include <ft2build.h>
#include FT_FREETYPE_H

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/font/fontglyph.hpp>

namespace CSELL { namespace Font {
    /*
        Static Class for abstracting away certain font functions from CSEA engine layer.
        Implemented using FreeType.
    */

    FontEngine::FontEngine() {}
    FontEngine::~FontEngine() {}

    bool FontEngine::isInitialized = false;
    FT_Library FontEngine::ft;
    std::map<std::string,FT_Face> FontEngine::fontFaceMap;
    std::map<std::string,std::map<std::pair<char,unsigned int>,FontGlyph*>> FontEngine::fontGlyphMap;

    bool FontEngine::initialize() {
        if (FontEngine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Font - FontEngine",
                             "Unable to initialize initialized Font Engine.");
            return false;
        }
        if (FT_Init_FreeType(&FontEngine::ft)) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Font - FontEngine",
                             "FreeType initialization failed.");
            return false;
        }
        FontEngine::isInitialized = true;
        return true;
    }

    void FontEngine::shutdown() {
        if (!FontEngine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Font - FontEngine",
                             "Unable to shutdown uninitialized Font Engine.");
            return;
        }
        if (FontEngine::fontFaceMap.size()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Font - FontEngine",
                             "Not all Fonts unloaded at time of shutdown.");
        }
        FT_Done_FreeType(ft);
        FontEngine::isInitialized = false;
    }

    bool FontEngine::loadFont(const std::string &fontPath, const std::string &fontKey) {
        if (!FontEngine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to load font: FontEngine is not initialized.");
            return false;
        }
        if (FontEngine::fontFaceMap.find(fontKey) != FontEngine::fontFaceMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to load font: Font key \"" + fontKey + "\" already exists.");
            return false;
        }
        FT_Face face;
        if (FT_New_Face(FontEngine::ft, fontPath.c_str(), 0, &face)) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to load font with path \"" + fontPath + "\".");
            return false;
        }
        FontEngine::fontFaceMap[fontKey] = face;
        FontEngine::fontGlyphMap[fontKey] = std::map<std::pair<char,unsigned int>,FontGlyph*>();
        return true;
    }

    bool FontEngine::unloadFont(const std::string &fontKey) {
        if (!FontEngine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to unload font: FontEngine is not initialized.");
            return false;
        }
        std::map<std::string,FT_Face>::iterator fontIt = FontEngine::fontFaceMap.find(fontKey);

        if (fontIt == FontEngine::fontFaceMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to unload font: Font key \"" + fontKey + "\" does not exist.");
            return false;
        }

        // erase loaded font glyphs
        std::map<std::string,std::map<std::pair<char,unsigned int>,FontGlyph*>>::iterator glyphMapIt;
        glyphMapIt = FontEngine::fontGlyphMap.find(fontKey);
        std::map<std::pair<char,unsigned int>,FontGlyph*>::iterator glyphIt;
        for (glyphIt = glyphMapIt->second.begin(); glyphIt != glyphMapIt->second.end(); ++glyphIt) {
            delete glyphIt->second;
        }
        FontEngine::fontGlyphMap.erase(glyphMapIt);
        FT_Done_Face(fontIt->second);
        FontEngine::fontFaceMap.erase(fontIt);

        return true;
    }

    FontGlyph *FontEngine::getGlyph(const std::string &fontKey, const char chr, unsigned int fontSize) {
        if (!FontEngine::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to get font: FontEngine is not initialized.");
            return NULL;
        }

        std::map<std::string,FT_Face>::iterator fontIt = FontEngine::fontFaceMap.find(fontKey);

        if (fontIt == FontEngine::fontFaceMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Font - FontEngine",
                             "Failed to get font: Font key \"" + fontKey + "\" does not exist.");
            return NULL;
        }

        std::map<std::pair<char,unsigned int>,FontGlyph*> glyphMap = FontEngine::fontGlyphMap.find(fontKey)->second;

        std::map<std::pair<char,unsigned int>,FontGlyph*>::iterator glyphIt;

        std::pair<char,unsigned int> charSizePair(chr,fontSize);

        glyphIt = glyphMap.find(charSizePair);

        if (glyphIt != glyphMap.end()) {
            return glyphIt->second;
        }

        // it's not in there... time to load...
        FT_Face &face = fontIt->second;

        FT_Set_Pixel_Sizes(face, 0, fontSize);

        if (FT_Load_Char(face, chr, FT_LOAD_RENDER)) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Font - FontEngine",
                             "Glyph unavailable: \"" + std::string(&chr) + "\"");
            return NULL;
        }

        // Note that advance resolves with 1/64 the actual value in pixels so right shift by 6
        FontGlyph *newGlyph = new FontGlyph(chr,
                                            face->glyph->bitmap_left, face->glyph->bitmap_top,
                                            face->glyph->bitmap.width, face->glyph->bitmap.rows,
                                            face->glyph->advance.x >> 6, face->glyph->bitmap.buffer);

        glyphMap[charSizePair] = newGlyph;

        return newGlyph;
    }
}}
