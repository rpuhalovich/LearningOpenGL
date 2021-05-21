#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Shader.hpp"

const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Ma window", false));
    std::unique_ptr<Shader> s (new Shader(vertexShaderSource));

    float verts[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // binds verts to currently bound buffer vbo

    while (!glfwWindowShouldClose(w->getWindow())) {
        // check input
        w->processInput(w->getWindow());

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
