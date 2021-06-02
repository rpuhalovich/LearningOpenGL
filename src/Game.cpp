#include <stb_image.h>
#include "Texture.hpp"
#include "Renderer.hpp"

std::vector<float> verts = {
     // positions       // colors   // texture coords
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
};

std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 3, 0
};

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Window", false, true));
    std::unique_ptr<ShaderProgram> sp1 (new ShaderProgram("vs.vert", "fs1.frag"));
    std::unique_ptr<Square> s1 (new Square(verts, indices));

    stbi_set_flip_vertically_on_load(true);

    // --- container texture ---
    unsigned int texture1, texture2;
    glc(glGenTextures(1, &texture1));
    glc(glBindTexture(GL_TEXTURE_2D, texture1));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // loading a texture
    int width, height, nrChannels;
    //std::cout << Texture::texloc("container.jpg") << std::endl;
    //unsigned char* data = stbi_load(Texture::texloc("container.jpg"), &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load((std::string(RES_DIR) + std::string("container.jpg")).c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        glc(glGenerateMipmap(GL_TEXTURE_2D)); // generates all mipmaps instead of doing it manually
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data);

    // --- face texture ---
    glc(glGenTextures(1, &texture2));
    glc(glBindTexture(GL_TEXTURE_2D, texture2));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // loading a texture
    data = stbi_load((std::string(RES_DIR) + std::string("awesomeface.png")).c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        glc(glGenerateMipmap(GL_TEXTURE_2D)); // generates all mipmaps instead of doing it manually
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data);

    // activate shader
    sp1->useProgram();
    glc(glUniform1i(glGetUniformLocation(sp1->getShaderProgram(), "texture1"), 0));
    glc(glUniform1i(glGetUniformLocation(sp1->getShaderProgram(), "texture2"), 1));

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        // render clear colour
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        glc(glActiveTexture(GL_TEXTURE0));
        glc(glBindTexture(GL_TEXTURE_2D, texture1));
        glc(glActiveTexture(GL_TEXTURE1));
        glc(glBindTexture(GL_TEXTURE_2D, texture2));

        // draw square1 (which is actually an upside down rgb triangle)
        s1->draw(texture1, texture2);

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
