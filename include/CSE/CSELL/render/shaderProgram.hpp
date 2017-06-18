#ifndef CSELL_RENDER_SHADER_PROGRAM_HPP
#define CSELL_RENDER_SHADER_PROGRAM_HPP

#include <string>

#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    class Renderer;

    class ShaderProgram {
    friend class Renderer;
        static unsigned int activeProgram;

        std::string programName;
        unsigned int programId;
        bool successfulLink;

        ShaderProgram(const std::string &programName, unsigned int nShaders, const Shader **shaders);
        ~ShaderProgram();
    public:
        std::string getName();
        void use();

        // uniform setters
        void setInt(const char *key, int value);
        void setFloat(const char *key, float value);
        void setMat4fv(const char *key, float *value);
    };
}}

#endif
