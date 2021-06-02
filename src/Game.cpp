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

    // --- container texture ---
    unsigned int texture;
    glc(glGenTextures(1, &texture));
    glc(glActiveTexture(GL_TEXTURE0));
    glc(glBindTexture(GL_TEXTURE_2D, texture));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // loading a texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(Texture::texloc("container.jpg"), &width, &height, &nrChannels, 0);

    if (data) {
        glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        glc(glGenerateMipmap(GL_TEXTURE_2D)); // generates all mipmaps instead of doing it manually
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data);

    // --- face texture ---
    unsigned int texture2;
    glc(glGenTextures(1, &texture2));
    glc(glActiveTexture(GL_TEXTURE1));
    glc(glBindTexture(GL_TEXTURE_2D, texture2));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // loading a texture
    unsigned char* data2 = stbi_load(Texture::texloc("awesomeface.png"), &width, &height, &nrChannels, 0);

    if (data2) {
        glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2));
        glc(glGenerateMipmap(GL_TEXTURE_2D)); // generates all mipmaps instead of doing it manually
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data2);

    // activate shader
    sp1->useProgram();


    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        // render clear colour
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        // draw square1 (which is actually an upside down rgb triangle)
        s1->draw(texture, texture2);

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
