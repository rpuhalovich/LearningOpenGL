#pragma once

#include <stb_image.h>

class Texture {
public:
    Texture(const char* filename);
    ~Texture();

private:
    unsigned char* data;
};