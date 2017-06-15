#include <string>

#include <lib/glad/glad.h>

#include <CSE/CSU/logger.hpp>
#include <CSE/CSELL/renderer/shader.hpp>


namespace CSELL { namespace Renderer {
    Shader::Shader(std::string const &shaderContents, const GLenum shaderType) {
        std::string strShaderType;
        if (shaderType == GL_VERTEX_SHADER) {
            strShaderType = "Vertex";
        } else if (shaderType == GL_FRAGMENT_SHADER) {
            strShaderType = "Fragment";
        } else {
            CSU::Logger::log(CSU::Logger::FATAL, CSU::Logger::CSELL, "Renderer - Shader Creation", "Please specify a valid shader Type!");
        }

        this->shaderId = glCreateShader(shaderType);

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
