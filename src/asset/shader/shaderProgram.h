#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>

#include <asset/shader/shader.h>

class ShaderProgram {
    unsigned int programId;
    bool finalized;
    std::vector<Shader*> shaders;
public:
    ShaderProgram();
    ~ShaderProgram();
    bool attachShader(Shader *shader);
    bool linkProgram();
    void setInt(const char *key, int value);
    void use();
};

#endif
