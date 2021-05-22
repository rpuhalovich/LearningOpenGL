#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glutil.hpp"

class Square {
public:
    Square();
    ~Square();

    void draw(); // make an interface?
private:
    float verts[12] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };

    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
    uint32_t size;
};
