#pragma once

#include <glad/glad.h>

#include "glutil.hpp"
#include "Shader.hpp"

enum class UniformType { m, v, p };

class ShaderProgram {
public:
    ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~ShaderProgram();

    void useProgram();

    unsigned int getShaderProgram() { return shaderProgram; }
    void setMat4(const glm::mat4& mat, UniformType type);

    void draw();
private:
    std::unique_ptr<Shader> vert;
    std::unique_ptr<Shader> frag;
    unsigned int shaderProgram;
};
