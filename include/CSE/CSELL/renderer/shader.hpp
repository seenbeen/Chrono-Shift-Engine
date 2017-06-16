#ifndef CSELL_RENDERER_SHADER_HPP
#define CSELL_RENDERER_SHADER_HPP

#include <string>

#include <glad/glad.h>

namespace CSELL { namespace Renderer {
    class Shader {
        unsigned int shaderId;
        bool successCompiled;
    public:
        enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };
        Shader(const std::string &shaderContents, Shader::ShaderType shaderType);
        ~Shader();
        unsigned int getId();
        bool compileSuccess();
    };
}}

#endif
