
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader(std::string source);
    ~Shader();

private:
    std::string source;
    unsigned int id;
};