#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const char* vertexShaderSourceName, const char* fragmentShaderSourceName) :
    vert(new Shader(std::string(Shader::readShaderFile(vertexShaderSourceName)), ShaderType::vertex)),
    frag (new Shader(std::string(Shader::readShaderFile(fragmentShaderSourceName)), ShaderType::fragment))
{
    glc(glEnable(GL_DEPTH_TEST)); // enables depth - allowing pixels in front to be drawn first
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
    glc(glUseProgram(shaderProgram));
}

void ShaderProgram::setMat4(const glm::mat4& mat, UniformType type) {
    switch (type) {
        case UniformType::m: {
            glm::mat4 model = glm::mat4(1.0f);
            model = mat;
            glc(unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model"));
            glc(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
            break;
        }
        case UniformType::v: {
            glm::mat4 view = glm::mat4(1.0f);
            view = mat;
            glc(unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view"));
            glc(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
            break;
        }
        case UniformType::p: {
            glm::mat4 projection;
            projection = mat;
            glc(unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection"));
            glc(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)));
            break;
        }
    }
}
