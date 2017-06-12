#include <image/stb_image.h>
#include <image/lodepng.h>
#include <vector>
#include <cstring>

#include <asset/image/image.h>

ImageAsset::ImageAsset(const char *filepath, bool isPNG) {
    unsigned char *temp;
    std::vector<unsigned char> image;
    if (isPNG) {
        lodepng::decode(image, this->imgW, this->imgH, filepath);
        this->nrChannels = 4;
        temp = &image[0];
    } else {
        int tw,th,tn;
        temp = stbi_load(filepath, &tw, &th, &tn, 0);
        this->imgW = (unsigned int)tw;
        this->imgH = (unsigned int)th;
        this->nrChannels = (unsigned int)tn;
    }

    unsigned int dataSize = this->imgW*this->imgH*this->nrChannels;

    this->imgData = new unsigned char[dataSize];
    std::memcpy(this->imgData, temp, dataSize);

    if (!isPNG) {
        stbi_image_free(temp);
    }

    this->vFlipImageData();
}

ImageAsset::~ImageAsset() {
    delete[] this->imgData;
}

void ImageAsset::vFlipImageData() {
    unsigned char temp;
    unsigned int lHeight = this->imgH/2;
    unsigned int lWidth = this->imgW*this->nrChannels;

    for (unsigned int i = 0; i < lHeight; i++) {
        for (unsigned int j = 0; j < lWidth; j++) {
            temp = this->imgData[i*lWidth+j];
            this->imgData[i*lWidth+j] = this->imgData[(this->imgH-i-1)*lWidth+j];
            this->imgData[(this->imgH-i-1)*lWidth+j] = temp;
        }
    }
}

unsigned int ImageAsset::width() { return this->imgW; }
unsigned int ImageAsset::height() { return this->imgH; }
unsigned int ImageAsset::nChannels() { return this->nrChannels; }
unsigned char *ImageAsset::data() { return this->imgData; }
