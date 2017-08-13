#ifndef CSEA_FONT_FONTRASTERIZER_HPP
#define CSEA_FONT_FONTRASTERIZER_HPP

#include <string>
#include <set>
#include <map>

#include <CSE/CSELL/font/fontengine.hpp>

#include <CSE/CSEA/font/rasterizedfont.hpp>

namespace CSEA { namespace Font {
    class FontRasterizer {
        FontRasterizer();
        ~FontRasterizer();

        static bool isInitialized;

        static std::set<char> CHARSET_ASCII;

        static std::map<std::string, RasterizedFont*> rFontMap;
        static std::set<std::string> fontsLoaded;

    public:
        static bool initialize();
        static void shutdown();

        static bool loadFont(const std::string &fontPath, const std::string &fontKey);

        static bool unloadFont(const std::string &fontKey);

        static bool rasterizeFont(const std::string &rFontKey, const std::string &fontKey, unsigned int fontSize, const std::set<char> &charset);

        static bool rasterizeFont(const std::string &rFontKey, const std::string &fontKey, unsigned int fontSize);

        static RasterizedFont *getRasterizedFont(const std::string &rFontKey);

        static void deleteRasterizedFont(const std::string &rFontKey);
    };
}}
#endif // CSEA_FONT_FONTRASTERIZER_HPP
