#ifndef CSELL_RENDER_SHADER_HPP
#define CSELL_RENDER_SHADER_HPP

#include <string>

namespace CSELL { namespace Render {
    class Renderer;
    class ShaderProgram;

    class Shader {
    friend class ShaderProgram;
    friend class Renderer;
    public:
        enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };
        std::string getName();
    private:
        unsigned int shaderId;
        bool successfulCompile;
        std::string shaderName;

        Shader(const std::string &shaderName, const std::string &shaderContents, Shader::ShaderType shaderType);
        ~Shader();
    };
}}

#endif
