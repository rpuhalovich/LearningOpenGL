#pragma once

#include <glad/glad.h>

#include "glutil.hpp"

enum class ShaderType { vertex, fragment };

static void checkShaderLink(const unsigned int id);

class Shader {
public:
    Shader(const std::string& source, ShaderType type);
    ~Shader();

    static std::string readShaderFile(const char* filename);

    unsigned int getID() { return id; }
private:
    std::string source;
    ShaderType type;
    unsigned int id;
};
