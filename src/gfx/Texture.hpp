#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "glutil.hpp"

class Texture {
public:
    Texture(const char * filename);
    ~Texture();
    unsigned int id;
private:
    int height;
    int width;
    int nrChannels;
};