#include "Window.hpp"

// putting prototypes in cpp files make the functions private like.
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

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

static glm::vec3 tempCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    tempCameraFront = glm::normalize(direction);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "x: " << xpos << " y: " << ypos << std::endl;
    }
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        glc(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        glc(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

    cameraFront = tempCameraFront;
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

bool Window::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void Window::beginFrame() {
    glc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // clears buffer every frame
    processInput();

    // render clear colour (bg)
    glc(glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w));
    glc(glClear(GL_COLOR_BUFFER_BIT));

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Window::endFrame() {
    // check and call events and swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}
