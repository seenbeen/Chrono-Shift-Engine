#ifndef CSELL_ASSETS_TEXT_HPP
#define CSELL_ASSETS_TEXT_HPP

#include <CSE/CSELL/asset/asset.hpp>

class AssetManager;

namespace CSELL { namespace Assets {
    class TextAsset : public Asset {
    friend class AssetManager;
        std::string *contents;
    protected:
        explicit TextAsset(const std::string &path);
        ~TextAsset();
    public:
        std::string *getContents();
    };
}}

#endif
