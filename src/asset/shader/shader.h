#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

class Shader {
    unsigned int shaderId;
    bool successCompiled;
public:
    Shader(const char *path, const GLenum shaderType);
    ~Shader();
    unsigned int getId();
    bool compileSuccess();
};

#endif
