#ifndef CSELL_RENDER_SHADER_HPP
#define CSELL_RENDER_SHADER_HPP

namespace CSELL { namespace Render {
    class Renderer;

    class Shader {
    friend class Renderer;
        Renderer *renderer;
        Renderer **activeRenderer;
    public:
        enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };
        virtual unsigned int getShaderId() = 0;
    protected:
        Shader();
        virtual ~Shader();
        virtual bool initShader(const char *shaderContents, Shader::ShaderType shaderType) = 0;
    };
}}

#endif
