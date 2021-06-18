#include <stb_image.h>
#include "Renderer.hpp"

int main(void) {
    std::unique_ptr<Window> w = std::make_unique<Window>(800, 600, "Window", false, true);
    std::unique_ptr<Texture> container = std::make_unique<Texture>("container.jpg");

    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("vs.vert", "fs.frag");
    std::unique_ptr<Square> s = std::make_unique<Square>(sp);

    sp->useProgram();

    glc(glEnable(GL_DEPTH_TEST));

    while (!w->shouldWindowClose()) {
        glc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        // check input
        w->processInput();

        // render clear colour (bg)
        glc(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glc(glClear(GL_COLOR_BUFFER_BIT));

        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // rotates the cube
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glc(unsigned int modelLoc = glGetUniformLocation(sp->getShaderProgram(), "model"));
        glc(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glc(unsigned int viewLoc = glGetUniformLocation(sp->getShaderProgram(), "view"));
        glc(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glc(unsigned int projectionLoc = glGetUniformLocation(sp->getShaderProgram(), "projection"));
        glc(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)));

        // draw square (which is actually an upside down rgb triangle)
        glc(glBindTexture(GL_TEXTURE_2D, container->id));
        glc(glBindVertexArray(s->vao));
        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i * (float)glfwGetTime();
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glc(unsigned int modelLoc = glGetUniformLocation(sp->getShaderProgram(), "model"));
            glc(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
            glc(glDrawArrays(GL_TRIANGLES, 0, 36));
        }

        // TODO: Abstract to window class
        // check and call events and swap buffers
        glfwSwapBuffers(w->getWindow());
        glfwPollEvents();
    }

    return 0;
}
