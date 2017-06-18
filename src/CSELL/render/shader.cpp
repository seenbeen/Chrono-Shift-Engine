#include <string>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>
#include <CSE/CSELL/render/shader.hpp>


namespace CSELL { namespace Render {
    Shader::Shader(const std::string &shaderName, const std::string &shaderContents, Shader::ShaderType shaderType) {
        this->shaderName = shaderName;

        std::string strShaderType;
        GLenum glShaderType;
        if (shaderType == Shader::VERTEX_SHADER) {
            strShaderType = "Vertex";
            glShaderType = GL_VERTEX_SHADER;
        } else if (shaderType == Shader::FRAGMENT_SHADER) {
            strShaderType = "Fragment";
            glShaderType = GL_FRAGMENT_SHADER;
        }

        this->shaderId = glCreateShader(glShaderType);

        const char *cstr = shaderContents.c_str();

        glShaderSource(this->shaderId, 1, &cstr, NULL);
        glCompileShader(this->shaderId);

        // check for success

        int compileSuccess;
        char statusMsg[512];
        glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess) {
            this->successfulCompile = true;
        } else {
            glGetShaderInfoLog(this->shaderId, 512, NULL, statusMsg);
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Render - Shader",
                             "Error compiling " + strShaderType + " Shader \"" + this->shaderName + "\":\n" + statusMsg);
            this->successfulCompile = false;
        }
    }

    Shader::~Shader() {
        glDeleteShader(this->shaderId);
    }

    std::string Shader::getName() {
        return this->shaderName;
    }
}}
