#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const char* vertexShaderSourceName, const char* fragmentShaderSourceName) :
    vert(new Shader(std::string(Shader::readShaderFile(vertexShaderSourceName)), ShaderType::vertex)),
    frag (new Shader(std::string(Shader::readShaderFile(fragmentShaderSourceName)), ShaderType::fragment))
{
    // create the shader program object
    glc(shaderProgram = glCreateProgram());
    glc(glAttachShader(shaderProgram, vert->getID()));
    glc(glAttachShader(shaderProgram, frag->getID()));
    glc(glLinkProgram(shaderProgram));
}

ShaderProgram::~ShaderProgram() {
    glc(glDeleteProgram(shaderProgram));
}

void ShaderProgram::useProgram() {
    glc(glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0));
    glc(glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1));

    glc(glUseProgram(shaderProgram));
}
