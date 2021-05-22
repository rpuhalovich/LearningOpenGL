#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glutil.hpp"
#include "Shader.hpp"

class ShaderProgram {
public:
    ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~ShaderProgram();
    
    void useProgram();
private:
    std::unique_ptr<Shader> vert;
    std::unique_ptr<Shader> frag;
    unsigned int shaderProgram;
};
