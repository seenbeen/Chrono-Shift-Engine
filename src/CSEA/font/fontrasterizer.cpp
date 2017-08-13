#include <CSE/CSEA/font/fontrasterizer.hpp>

#include <utility>
#include <string>
#include <set>
#include <map>
#include <list>

#include <CSE/CSU/utilities.hpp>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/font/fontengine.hpp>

#include <CSE/CSEA/font/rasterizedfont.hpp>

namespace CSEA { namespace Font {
    FontRasterizer::FontRasterizer() {}
    FontRasterizer::~FontRasterizer() {}

    bool FontRasterizer::isInitialized = false;

    std::set<char> FontRasterizer::CHARSET_ASCII;

    std::map<std::string, RasterizedFont*> FontRasterizer::rFontMap;
    std::set<std::string> FontRasterizer::fontsLoaded;

    bool FontRasterizer::initialize() {
        if (FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Initializing initialized Rasterizer.");
            return false;
        }
        for (unsigned int i = 0; i < 128; ++i) {
            FontRasterizer::CHARSET_ASCII.insert(i);
        }
        FontRasterizer::isInitialized = CSELL::Font::FontEngine::initialize();
        return FontRasterizer::isInitialized;
    }

    void FontRasterizer::shutdown() {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Cannot shutdown uninitialized Rasterizer.");
            return;
        }
        CSELL::Font::FontEngine::shutdown();
        FontRasterizer::isInitialized = false;
    }

    bool FontRasterizer::loadFont(const std::string &fontPath, const std::string &fontKey) {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to loadFont: FontRasterizer is not initialized.");
            return false;
        }

        if (FontRasterizer::fontsLoaded.find(fontKey) != FontRasterizer::fontsLoaded.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to loadFont: \"" + fontKey + "\" already exists.");
            return false;
        }

        if (!CSELL::Font::FontEngine::loadFont(fontPath, fontKey)) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to loadFont: FontEngine failed to load \"" + fontPath + "\".");
            return false;
        }

        FontRasterizer::fontsLoaded.insert(fontKey);

        return true;
    }

    bool FontRasterizer::unloadFont(const std::string &fontKey) {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to unloadFont: FontRasterizer is not initialized.");
            return false;
        }

        std::set<std::string>::iterator it = FontRasterizer::fontsLoaded.find(fontKey);

        if (it == FontRasterizer::fontsLoaded.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to unloadFont: \"" + fontKey + "\" does not exist.");
            return false;
        }

        if (!CSELL::Font::FontEngine::unloadFont(fontKey)) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to unloadFont: FontEngine failed to unload \"" + fontKey + "\".");
            return false;
        }

        FontRasterizer::fontsLoaded.erase(it);

        return true;
    }

    bool FontRasterizer::rasterizeFont(const std::string &rFontKey, const std::string &fontKey, unsigned int fontSize, const std::set<char> &charset) {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to rasterizeFont: FontRasterizer is not initialized.");
            return false;
        }

        if (FontRasterizer::fontsLoaded.find(fontKey) == FontRasterizer::fontsLoaded.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to rasterizeFont: \"" + fontKey + "\" does not exist.");
            return false;
        }

        std::map<std::string, RasterizedFont*>::iterator it = FontRasterizer::rFontMap.find(rFontKey);

        if (it != FontRasterizer::rFontMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to rasterizeFont: Rasterized Key \"" + rFontKey + "\" already exists.");
            return false;
        }

        std::list<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> lst;

        CSELL::Font::FontGlyph **glyphs = new CSELL::Font::FontGlyph *[charset.size()];

        int ctr = 0;
        for (auto c: charset) {
            glyphs[ctr] = CSELL::Font::FontEngine::getGlyph(fontKey, c, fontSize);
            if (glyphs[ctr] != NULL) {
                lst.push_back({ctr, {glyphs[ctr]->width, glyphs[ctr]->height}});
            } else {
                CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                                 "Unable to rasterize char: \"" + std::string(&c) + "\".");
            }
            ++ctr;
        }

        unsigned int resultW = 0;
        unsigned int resultH = 0;

        CSU::Utilities::packRects(lst,resultW, resultH);

        unsigned int packingOrder[lst.size()];
        std::map<char, unsigned int> glyphMap;

        ctr = 0;
        for (auto rect: lst) {
            packingOrder[ctr] = rect.first;
            glyphMap[glyphs[rect.first]->chr] = rect.first;
            ctr++;
        }

        FontRasterizer::rFontMap[rFontKey] = new RasterizedFont(glyphMap, lst.size(), packingOrder,
                                                                glyphs, resultW, resultH);
        return true;
    }

    bool FontRasterizer::rasterizeFont(const std::string &rFontKey, const std::string &fontKey, unsigned int fontSize) {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to rasterizeFont: FontRasterizer is not initialized.");
            return false;
        }
        return FontRasterizer::rasterizeFont(rFontKey, fontKey, fontSize, FontRasterizer::CHARSET_ASCII);
    }

    RasterizedFont *FontRasterizer::getRasterizedFont(const std::string &rFontKey) {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to getRasterizedFont: FontRasterizer is not initialized.");
            return NULL;
        }
        std::map<std::string, RasterizedFont*>::iterator it = FontRasterizer::rFontMap.find(rFontKey);
        if (it == FontRasterizer::rFontMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to getRasterizedFont: Rasterized Key \"" + rFontKey + "\" does not exist.");
            return NULL;
        }
        return it->second;
    }

    void FontRasterizer::deleteRasterizedFont(const std::string &rFontKey) {
        if (!FontRasterizer::isInitialized) {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to deleteRasterizedFont: FontRasterizer is not initialized.");
            return;
        }
        std::map<std::string, RasterizedFont*>::iterator it = FontRasterizer::rFontMap.find(rFontKey);
        if (it == FontRasterizer::rFontMap.end()) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSEA, "Font - FontRasterizer",
                             "Unable to getRasterizedFont: Rasterized Key \"" + rFontKey + "\" does not exist.");
            return;
        }
        delete it->second;
        FontRasterizer::rFontMap.erase(it);
    }
}}
