#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include "Renderer.hpp"

const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Mah Window", false, true));
    std::unique_ptr<ShaderProgram> sp (new ShaderProgram(vertexShaderSource, fragmentShaderSource));
    std::unique_ptr<Square> s1 (new Square());

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        //render
        glc(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        sp->useProgram(); // probably abstract to render class or somethin (facade?)
        s1->draw();

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
