#include "Window.hpp"

// putting prototypes in cpp files make the functions private like.
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Window::Window(unsigned int width, unsigned int height, const std::string& title, bool maximised, bool resizable) :
    width(width), height(height), title(title), maximised(maximised), resizable(resizable)
{
    window = makeWindow(width, height, title.c_str(), maximised, resizable);
    gladInit(window, width, height);
#ifdef DEB
    std::cout << glGetString(GL_VERSION) << std::endl;
#endif

    stbi_set_flip_vertically_on_load(true);
}

Window::~Window() {
    glfwTerminate();
}

GLFWwindow* Window::makeWindow(int width, int height, const char* title, bool maximized, bool resizable) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, maximized ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    return window;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glc(glViewport(0, 0, width, height));
}

void Window::gladInit(GLFWwindow* window, int width, int height) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "x: " << xpos << " y: " << ypos << std::endl;
    }
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glc(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        glc(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    }
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

bool Window::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}
