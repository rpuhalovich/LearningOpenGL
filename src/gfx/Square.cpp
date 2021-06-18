#include "Square.hpp"

Square::Square(std::shared_ptr<ShaderProgram> shader) :
    shader(shader)
{
    glc(glGenVertexArrays(1, &vao));
    glc(glGenBuffers(1, &vbo));
    glc(glGenBuffers(1, &ebo));

    // 1. bind Vertex Array Object
    glc(glBindVertexArray(vao));

    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glc(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    // binds verts to currently bound buffer vbo
    glc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts.size(), &verts[0], GL_STATIC_DRAW));

    // 3. copy our index array in a element buffer for OpenGL to use
    glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    glc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW));

    // 4. then set the vertex attributes pointers
    // positions
    glc(glEnableVertexAttribArray(0));
    glc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));

    // texture
    glc(glEnableVertexAttribArray(1));
    glc(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));

    glc(glBindVertexArray(0)); // unbinds vao for later use - ensure it's unbound before the vbo/ebo unbind
    glc(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

Square::~Square() {
    glc(glDeleteVertexArrays(1, &vao));
    glc(glDeleteBuffers(1, &vbo));
    glc(glDeleteBuffers(1, &ebo));
}

void Square::draw(unsigned int texID) {
    glc(glBindTexture(GL_TEXTURE_2D, texID));
    glc(glBindVertexArray(vao));
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}
