#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include "Renderer.hpp"

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Window", false, true));
    std::unique_ptr<ShaderProgram> sp1 (new ShaderProgram("vs.vert", "fs1.frag"));
    std::unique_ptr<ShaderProgram> sp2 (new ShaderProgram("vs.vert", "fs2.frag"));

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

    std::unique_ptr<Square> s1 (new Square(verts, indices));

    verts = {
         1.0f,  1.0f, 0.0f,
         1.0f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f,  1.0f, 0.0f
    };

    std::unique_ptr<Square> s2 (new Square(verts, indices));

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        //render
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        sp1->useProgram(); // probably abstract to render class or somethin (facade?)
        s1->draw();
        sp2->useProgram();
        (*s2).draw(); // just reminding myself of dot vs arrow notation

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
