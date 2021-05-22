#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) :
    vert(new Shader(std::string(vertexShaderSource), ShaderType::vertex)),
    frag (new Shader(std::string(fragmentShaderSource), ShaderType::fragment))
{
    // create the shader program object
    glc(shaderProgram = glCreateProgram());
    glc(glAttachShader(shaderProgram, vert->getID()));
    glc(glAttachShader(shaderProgram, frag->getID()));
    glc(glLinkProgram(shaderProgram));
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(shaderProgram);
}

void ShaderProgram::useProgram() {
    glUseProgram(shaderProgram);
}
