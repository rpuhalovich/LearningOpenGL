#pragma once

#include <glad/glad.h>

#include "glutil.hpp"
#include "Shader.hpp"

class ShaderProgram {
public:
    ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~ShaderProgram();

    void useProgram();

    unsigned int getShaderProgram() { return shaderProgram; }
    void setMat4(const std::string& name, const glm::mat4& value);
private:
    std::unique_ptr<Shader> vert;
    std::unique_ptr<Shader> frag;
    unsigned int shaderProgram;
};
