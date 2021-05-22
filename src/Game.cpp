#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    std::unique_ptr<Shader> vert (new Shader(std::string(vertexShaderSource), ShaderType::vertex));
    std::unique_ptr<Shader> frag (new Shader(std::string(fragmentShaderSource), ShaderType::fragment));

    // TODO: abstract into ShaderProgram class
    // create the shader program object
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vert->getID());
    glAttachShader(shaderProgram, frag->getID());
    glLinkProgram(shaderProgram);
    
    float verts[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    
    // don't put these as floats, unsigned ints only!!
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
   
    // 1. bind Vertex Array Object
    glBindVertexArray(vao);

    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // binds verts to currently bound buffer vbo
    
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);

    return 0;
}
