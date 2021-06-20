#include "Renderer.hpp"

int main(void) {
    unsigned int wWidth = 800, wHeight = 600;
    std::unique_ptr<Window> w = std::make_unique<Window>(wWidth, wHeight, "Window", false, true);
    std::unique_ptr<Texture> container = std::make_unique<Texture>("container.jpg");

    std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>("vs.vert", "fs.frag");
    std::unique_ptr<Square> s = std::make_unique<Square>(sp);

    sp->useProgram();

    glm::mat4 view = glm::mat4(1.0f);

    while (!w->shouldWindowClose()) {
        w->beginFrame();

        // --- mvp for the containers ---
        // model
        glm::mat4 model = glm::mat4(1.0f);
        sp->setMat4(glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)), UniformType::m);

        // setting view matrix for camera view
        view = glm::lookAt(w->cameraPos, w->cameraPos + w->cameraFront, w->cameraUp);
        sp->setMat4(view, UniformType::v);

        // perspective (should really only be set once)
        sp->setMat4(glm::perspective(glm::radians(45.0f), (float)wWidth / (float)wHeight, 0.1f, 100.0f), UniformType::p);

        // draw containers
        s->draw(container->id);
        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i * (float)glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));
            sp->setMat4(model, UniformType::m);
            glc(glDrawArrays(GL_TRIANGLES, 0, 36));
        }

        w->endFrame();
    }

    return 0;
}
