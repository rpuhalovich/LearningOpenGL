#pragma once

#include <stb_image.h>

class Texture {
public:
    Texture(const char * filename, int x);
    ~Texture();

    void readTexture();
private:
    unsigned char* data;
};