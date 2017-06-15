#ifndef IMAGE_ASSET_H
#define IMAGE_ASSET_H

namespace CSELL { namespace Asset {
    class ImageAsset {
        unsigned char *imgData;
        unsigned int imgW, imgH, nrChannels;
    public:
        ImageAsset(const char *filepath, bool isPNG);
        ~ImageAsset();
        void vFlipImageData();
        unsigned int width();
        unsigned int height();
        unsigned int nChannels();
        unsigned char *data();
    };
}}

#endif
