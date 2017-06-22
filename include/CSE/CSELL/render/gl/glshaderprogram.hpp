#ifndef CSELL_RENDER_GL_GLSHADERPROGRAM_HPP
#define CSELL_RENDER_GL_GLSHADERPROGRAM_HPP

#include <vector>

#include <CSE/CSELL/render/shaderprogram.hpp>

namespace CSELL { namespace Render {
    class Shader;

    class GLShaderProgram: public ShaderProgram {
        unsigned int programId;
        std::vector<Shader *> shaders;

    protected:
        ~GLShaderProgram();

        bool initShaderProgram();

        bool attachShaderImplementation(Shader *shader);
        bool linkShaderProgramImplementation();
        bool useShaderProgramImplementation();

        // uniform setter implementations
        bool setIntImplementation(const char *key, int value);
        bool setFloatImplementation(const char *key, float value);
        bool setMat4fImplementation(const char *key, float *value);
    };
}}

#endif
