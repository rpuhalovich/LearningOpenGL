#include "Square.hpp"

Square::Square() {
    /**
     * Process for creating an object to draw to the screen.
     * 1. get vertecies and indicies
     * 2. generate the vao that you're going to fill with vbos and ebos and bind it
     * 3. bind vbo and fill with verts, do the same with ebo and indicies
     * 4. set up the glvertexattribpointer settings and enable it
     * 5. unbind the latest GL_ARRAY_BUFFER (be it a vbo or ebo) and unbind the vao
     *
     * The vao is a container for the vbo and ebo objects that you're to use to draw to the screen.
     * You then rebind the vao that you want to draw to the screen and then draw it.
     * Ensure you're using glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0) to draw using the ebo.
     */

    // TODO: Make these configurable
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

    glc(glBindVertexArray(0)); // unbinds vao for later use - ensure it's unbound before the vbo/ebo unbind
    glc(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

Square::~Square() {
    glc(glDeleteVertexArrays(1, &vao));
    glc(glDeleteBuffers(1, &vbo));
    glc(glDeleteBuffers(1, &ebo));
}

void Square::draw() {
    glc(glBindVertexArray(vao));
    glc(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}
