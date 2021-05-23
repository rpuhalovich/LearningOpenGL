#include "Shader.hpp"

#define INFO_LOG_LEN 512

Shader::Shader(const std::string& source, ShaderType type) : 
    source(source), type(type)
{
    if (type == ShaderType::vertex) {
        glc(id = glCreateShader(GL_VERTEX_SHADER));
    } else if (type == ShaderType::fragment) {
        glc(id = glCreateShader(GL_FRAGMENT_SHADER));
    }

    const char* src = source.c_str();
    glc(glShaderSource(id, 1, &src, NULL));
    glc(glCompileShader(id));

    int success;
    char infoLog[INFO_LOG_LEN];
    glc(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success) {
        glc(glGetShaderInfoLog(id, INFO_LOG_LEN, NULL, infoLog));
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glc(glDeleteShader(id));
}

static void checkShaderLink(const unsigned int id) {
    int success;
    char infoLog[INFO_LOG_LEN];
    glc(glGetProgramiv(id, GL_COMPILE_STATUS, &success));
    if (!success) {
        glc(glGetProgramInfoLog(id, INFO_LOG_LEN, NULL, infoLog));
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
