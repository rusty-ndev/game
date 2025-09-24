#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
public:
    GLuint ID;

    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;
};

