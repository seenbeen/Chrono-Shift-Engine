#include <vector>
#include <string>

#include <lib/image/stb_image.h>

#include <CSE/CSELL/asset/image.hpp>

namespace CSELL { namespace Assets {
    ImageAsset::ImageAsset(const std::string &filepath) {
        unsigned char *temp;
        int tw,th,tn;

        temp = stbi_load(filepath.c_str(), &tw, &th, &tn, 0);
        this->imgW = (unsigned int)tw;
        this->imgH = (unsigned int)th;

        unsigned int dataSize = this->imgW*this->imgH*4;

        this->imgData = new unsigned char[dataSize];

        unsigned int tempCounter = 0;
        unsigned int nChan = (unsigned int)tn;

        for (unsigned int i = 0; i < dataSize; ++i) {
            if (i%4 < nChan) {
                this->imgData[i] = temp[tempCounter++];
            } else {
                this->imgData[i] = 255;
            }
        }

        stbi_image_free(temp);

        dataSize /= 4;
        // set all invisible pixels to white
        for (unsigned int i = 0; i < dataSize; ++i) {
            if (this->imgData[i*4+3] == 0) {
                for (unsigned int j = 0; j < 3; ++j) {
                    this->imgData[i*4+j] = 255;
                }
            }
        }

        this->vFlipImageData();
    }

    ImageAsset::~ImageAsset() {
        delete[] this->imgData;
    }

    void ImageAsset::vFlipImageData() {
        unsigned char temp;
        unsigned int lHeight = this->imgH/2;
        unsigned int lWidth = this->imgW*4;

        for (unsigned int i = 0; i < lHeight; ++i) {
            for (unsigned int j = 0; j < lWidth; ++j) {
                temp = this->imgData[i*lWidth+j];
                this->imgData[i*lWidth+j] = this->imgData[(this->imgH-i-1)*lWidth+j];
                this->imgData[(this->imgH-i-1)*lWidth+j] = temp;
            }
        }
    }

    unsigned int ImageAsset::width() { return this->imgW; }
    unsigned int ImageAsset::height() { return this->imgH; }
    unsigned char *ImageAsset::data() { return this->imgData; }
}}
