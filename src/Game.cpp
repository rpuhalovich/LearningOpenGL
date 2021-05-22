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
    std::unique_ptr<Window> w (new Window(800, 600, "Mah Window", false));
    std::unique_ptr<ShaderProgram> sp (new ShaderProgram(vertexShaderSource, fragmentShaderSource));
    
    float verts[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int vao, vbo, ebo;
    glc(glGenVertexArrays(1, &vao));
    glc(glGenBuffers(1, &vbo));
    glc(glGenBuffers(1, &ebo));
   
    // 1. bind Vertex Array Object
    glc(glBindVertexArray(vao));

    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glc(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    glc(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW)); // binds verts to currently bound buffer vbo
    
    // 3. copy our index array in a element buffer for OpenGL to use
    glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    glc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 4. then set the vertex attributes pointers
    glc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    glc(glEnableVertexAttribArray(0));
    
    glc(glBindBuffer(GL_ARRAY_BUFFER, 0));
    glc(glBindVertexArray(0));

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        //render
        glc(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        sp->useProgram(); // probably abstract to render class or somethin (facade?)
        glc(glBindVertexArray(vao));
        glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }
    
    glc(glDeleteVertexArrays(1, &vao));
    glc(glDeleteBuffers(1, &vbo));
    glc(glDeleteBuffers(1, &ebo));
    
    return 0;
}
