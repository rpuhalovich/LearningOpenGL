#pragma once

#include <glad/glad.h>

#include "glutil.hpp"

// TODO: Abstract all OpenGL code to shape class and put Square into a seperate folder from gfx.

class Square {
public:
    Square(const std::vector<float>& verts, const std::vector<unsigned int>& indices);
    ~Square();

    void draw(unsigned int textureID1);
private:
    // I'm sure these can be abstracted to a general shape class.
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
};
