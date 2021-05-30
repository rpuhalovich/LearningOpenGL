#include <stb_image.h>
#include "Renderer.hpp"

std::vector<float> verts = {
     // positions       // colors
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Window", false, true));
    std::unique_ptr<ShaderProgram> sp1 (new ShaderProgram("vs.vert", "fs1.frag"));
    std::unique_ptr<Square> s1 (new Square(verts, indices));

    // loading a texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load((std::string(RES_DIR) + "container.jpg").c_str(), &width, &height, &nrChannels, 0);
    unsigned int texture;
    glc(glGenTextures(1, &texture));

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        // render clear colour
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        // activate shader
        sp1->useProgram();
        s1->draw();

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
