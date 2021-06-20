#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "glutil.hpp"

class Window {
public:
    Window(unsigned int width, unsigned int height, const std::string& title, bool maximised, bool resizable);
    ~Window();

    /**
     * \return GLFWwindow pointer with the specified params.
     */
    GLFWwindow* makeWindow(int width, int height, const char* title, bool maximized, bool resizable);
    void gladInit(GLFWwindow* window, int width, int height);
    
    void beginFrame();
    void endFrame();

    /**
     * Perhaps create a listener class to handle the input?
     */
    void processInput();
    bool shouldWindowClose();

    unsigned int getWidth() { return width; }
    unsigned int getHeight() { return height; }
    GLFWwindow* getWindow() { return window; }

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp  = glm::vec3(0.0f, 1.0f,  0.0f);
    
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
private:
    glm::vec4 clearColour = glm::vec4(0.2f, 0.1f, 0.2f, 1.0f);

    unsigned int width;
    unsigned int height;
    std::string title;
    bool maximised;
    bool resizable;

    GLFWwindow* window;
    
};
