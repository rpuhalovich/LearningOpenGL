#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include "Renderer.hpp"

std::vector<float> verts = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

std::vector<unsigned int> indices = {
    0, 1, 3,
    1, 2, 3
};

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Window", false, true));
    std::unique_ptr<ShaderProgram> sp1 (new ShaderProgram("vs.vert", "fs1.frag"));
    std::unique_ptr<Square> s1 (new Square(verts, indices));

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        //render
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        float timeValue = glfwGetTime();
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        glc(int vertexColorLocation = glGetUniformLocation(sp1->getShaderProgram(), "ourColor"));
        sp1->useProgram();
        glc(glUniform4d(vertexColorLocation, 0.0f, redValue, 0.0f, 1.0f));

        //sp1->useProgram(); // probably abstract to render class or somethin (facade?)
        s1->draw();

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
