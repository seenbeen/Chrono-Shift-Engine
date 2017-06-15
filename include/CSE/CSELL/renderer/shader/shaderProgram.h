#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>

#include <CSE/CSELL/renderer/shader/shader.h>

namespace CSELL { namespace Renderer {
    class ShaderProgram {
        unsigned int programId;
        bool finalized;
        std::vector<Shader*> shaders;
    public:
        ShaderProgram();
        ~ShaderProgram();
        bool attachShader(Shader *shader);
        bool linkProgram();
        void use();

        // uniform setters
        void setInt(const char *key, int value);
        void setFloat(const char *key, float value);
        void setMat4fv(const char *key, float *value);
    };
}}

#endif
