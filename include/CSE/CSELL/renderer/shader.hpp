#ifndef CSELL_RENDERER_SHADER_HPP
#define CSELL_RENDERER_SHADER_HPP

#include <glad/glad.h>

namespace CSELL { namespace Renderer {
    class Shader {
        unsigned int shaderId;
        bool successCompiled;
    public:
        Shader(const char *path, const GLenum shaderType);
        ~Shader();
        unsigned int getId();
        bool compileSuccess();
    };
}}

#endif
