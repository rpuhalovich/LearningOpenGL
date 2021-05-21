
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(unsigned int width, unsigned int height, std::string title, bool maximised);
    ~Window();

    GLFWwindow* makeWindow(int width, int height, const char* title, bool maximized);
    void gladInit(GLFWwindow* window, int width, int height);
    void processInput();
    bool shouldWindowClose();

    unsigned int getWidth() { return width; }
    unsigned int getHeight() { return height; }
    GLFWwindow* getWindow() { return window; }
private:
    unsigned int width;
    unsigned int height;
    std::string title;
    bool maximised;

    GLFWwindow* window;
};
