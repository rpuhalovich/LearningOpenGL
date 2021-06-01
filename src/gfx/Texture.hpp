#pragma once

#include <stb_image.h>

class Texture {
public:
    Texture(const char * filename, int x);
    ~Texture();

    static const char* texloc(const char* texname);
private:
    unsigned char* data;
};