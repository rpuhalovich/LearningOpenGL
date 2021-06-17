#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>
#include "Texture.hpp"
#include "Renderer.hpp"

std::vector<float> verts = {
     // positions       // colors   // texture coords
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
};

std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 3, 0
};

int main(void) {
    std::unique_ptr<Window> w (new Window(800, 600, "Window", false, true));
    std::unique_ptr<ShaderProgram> sp1 (new ShaderProgram("vs.vert", "fs1.frag"));
    std::unique_ptr<Square> s1 (new Square(verts, indices));
    std::unique_ptr<Texture> container (new Texture("container.jpg"));

    sp1->useProgram();

    while (!w->shouldWindowClose()) {
        // check input
        w->processInput();

        // container transformation
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5, 0.5, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

        glc(unsigned int transformLoc = glGetUniformLocation(sp1->getShaderProgram(), "transform"));
        glc(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)));

        // render clear colour (bg)
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        // draw square1 (which is actually an upside down rgb triangle)
        s1->draw(container->id);

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
