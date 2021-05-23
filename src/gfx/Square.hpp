#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glutil.hpp"

// TODO: Abstract all OpenGL code to shape class and put Square into a seperate folder from gfx.

class Square {
public:
    Square(const std::vector<float>& verts, const std::vector<unsigned int>& indices);
    ~Square();

    void draw(); // make an interface?
private:
    //float* verts;
    //unsigned int* indices;

    // I'm sure these can be abstracted to a general shape class.
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
};
