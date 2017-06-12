#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <asset/image/image.h>

class Texture {
protected:
    unsigned int textureId;
public:
    Texture(ImageAsset *image);
    ~Texture();
    void useActiveTexture(GLenum textureNumber);
};

class Texture2D : public Texture {
public:
    Texture2D(ImageAsset *image);
};
#endif
