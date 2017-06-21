#ifndef CSELL_RENDER_GL_GLSHADER_HPP
#define CSELL_RENDER_GL_GLSHADER_HPP

#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    class GLShader : public Shader {
        unsigned int shaderId;
    protected:
        ~GLShader();
        bool initShader(const char *shaderContents, Shader::ShaderType shaderType);
    public:
        unsigned int getShaderId();
    };
}}

#endif
