#include "Texture.hpp"

Texture::Texture(const char* filename) {
    // --- container texture ---
    glc(glGenTextures(1, &id));
    glc(glBindTexture(GL_TEXTURE_2D, id));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // loading a texture
    unsigned char* data = stbi_load((std::string(RES_DIR) + std::string(filename)).c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        glc(glGenerateMipmap(GL_TEXTURE_2D)); // generates all mipmaps instead of doing it manually
    }
    else {
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture() {

}
