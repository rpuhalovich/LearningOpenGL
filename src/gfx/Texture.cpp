#include "Texture.hpp"

Texture::Texture(const char* filename, int x)
{
}

Texture::~Texture()
{
}

const char* Texture::texloc(const char* texname) {
    return (std::string(RES_DIR) + std::string(texname)).c_str();
}
