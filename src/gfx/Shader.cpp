#include "Shader.hpp"

#define INFO_LOG_LEN 512

Shader::Shader(std::string source, ShaderType type) : source(source), type(type) {
    if (type == ShaderType::vertex) {
        id = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == ShaderType::fragment) {
        id = glCreateShader(GL_FRAGMENT_SHADER);
    } else {
        std::cout << "How did you mess this up?\n";
        exit(EXIT_FAILURE);
    }

    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int success;
    char infoLog[INFO_LOG_LEN];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, INFO_LOG_LEN, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader() {}
