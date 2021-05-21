
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class ShaderType { vertex, fragment };

class Shader {
public:
    Shader(std::string source, ShaderType type);
    ~Shader();

private:
    std::string source;
    ShaderType type;
    unsigned int id;
};