#include "Shader.hpp"

#define INFO_LOG_LEN 512

Shader::Shader(std::string source) : source(source) {
    id = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int success;
    char infoLog[INFO_LOG_LEN];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, INFO_LOG_LEN, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader() {}
