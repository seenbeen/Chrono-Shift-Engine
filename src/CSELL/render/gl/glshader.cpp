#include <string>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>

#include <CSE/CSELL/render/gl/glshader.hpp>
#include <CSE/CSELL/render/shader.hpp>

namespace CSELL { namespace Render {
    bool GLShader::initShader(const char *shaderContents, Shader::ShaderType shaderType) {
        std::string strShaderType;
        GLenum glShaderType = Shader::VERTEX_SHADER; // prevent complaining abount un-init
        if (shaderType == Shader::VERTEX_SHADER) {
            strShaderType = "Vertex";
            glShaderType = GL_VERTEX_SHADER;
        } else if (shaderType == Shader::FRAGMENT_SHADER) {
            strShaderType = "Fragment";
            glShaderType = GL_FRAGMENT_SHADER;
        }

        this->shaderId = glCreateShader(glShaderType);

        glShaderSource(this->shaderId, 1, &shaderContents, NULL);
        glCompileShader(this->shaderId);

        // check for success

        int compileSuccess;

        glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &compileSuccess);

        if (compileSuccess == 0) {
            char statusMsg[512];
            glGetShaderInfoLog(this->shaderId, 512, NULL, statusMsg);
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Shader",
                             "Error compiling " + strShaderType + " Shader:\n" + statusMsg);
        }
        return compileSuccess != 0;
    }

    GLShader::~GLShader() {
        glDeleteShader(this->shaderId);
    }

    unsigned int GLShader::getShaderId() {
        return this->shaderId;
    }
}}
