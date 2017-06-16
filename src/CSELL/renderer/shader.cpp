#include <string>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>
#include <CSE/CSELL/renderer/shader.hpp>


namespace CSELL { namespace Renderer {
    Shader::Shader(const std::string &shaderContents, Shader::ShaderType shaderType) {
        std::string strShaderType;
        GLenum glShaderType;
        if (shaderType == Shader::VERTEX_SHADER) {
            strShaderType = "Vertex";
            glShaderType = GL_VERTEX_SHADER;
        } else if (shaderType == Shader::FRAGMENT_SHADER) {
            strShaderType = "Fragment";
            glShaderType = GL_FRAGMENT_SHADER;
        } else {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Renderer - Shader Creation", "Please specify a valid shader Type!");
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
            this->successCompiled = true;
        } else {
            glGetShaderInfoLog(this->shaderId, 512, NULL, statusMsg);
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Renderer - " + strShaderType + " Shader Compilation", statusMsg);
            this->successCompiled = false;
        }
    }

    unsigned int Shader::getId() {
        return this->shaderId;
    }

    bool Shader::compileSuccess() {
        return this->successCompiled;
    }

    Shader::~Shader() {
        glDeleteShader(this->shaderId);
    }
}}
