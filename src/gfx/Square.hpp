#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glutil.hpp"

class Square {
public:
    Square();
    ~Square();

    void draw(); // make an interface?
private:
    //float* verts;
    //unsigned int* indices;

    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
};
