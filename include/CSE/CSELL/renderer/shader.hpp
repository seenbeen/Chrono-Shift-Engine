#ifndef CSELL_RENDERER_SHADER_HPP
#define CSELL_RENDERER_SHADER_HPP

#include <string>

#include <glad/glad.h>

namespace CSELL { namespace Renderer {
    class Shader {
        unsigned int shaderId;
        bool successCompiled;
    public:
        Shader(std::string const &shaderContents, const GLenum shaderType);
        ~Shader();
        unsigned int getId();
        bool compileSuccess();
    };
}}

#endif
