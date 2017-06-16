#ifndef CSELL_ASSETS_IMAGE_HPP
#define CSELL_ASSETS_IMAGE_HPP

#include <string>

#include <CSE/CSELL/asset/asset.hpp>

class AssetManager;

namespace CSELL { namespace Assets {
    class ImageAsset : public Asset {
    friend class AssetManager;
        unsigned char *imgData;
        unsigned int imgW, imgH;
    protected:
        ImageAsset(const std::string &filepath, bool isPNG);
        ~ImageAsset();
    public:
        void vFlipImageData();
        unsigned int width();
        unsigned int height();
        unsigned char *data();
    };
}}

#endif
