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
private:
    glm::vec4 clearColour = glm::vec4(0.2f, 0.1f, 0.2f, 1.0f);
    
    unsigned int width;
    unsigned int height;
    std::string title;
    bool maximised;
    bool resizable;

    GLFWwindow* window;
};
