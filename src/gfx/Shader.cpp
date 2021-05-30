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

std::string Shader::readShaderFile(const char* filename) {
    std::ifstream in(std::string(SHADER_DIR) + std::string(filename));
    if (!in) {
        std::cout << "Error reading file." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return s;
}
